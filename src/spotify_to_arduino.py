import time
import serial
from SwSpotify import spotify, SpotifyNotRunning
import lyricsgenius

# === CONFIGURATION SUBSYSTEM ===
GENIUS_TOKEN = "YOUR_GENIUS_ACCESS_TOKEN_HERE" 
ARDUINO_PORT = 'COM3' 
BAUD_RATE = 115200
# ===============================

try:
    arduino = serial.Serial(port=ARDUINO_PORT, baudrate=BAUD_RATE, timeout=.1)
    print(f"✓ Established Serial connection on {ARDUINO_PORT}")
except Exception as e:
    print(f"✗ Failed to connect on port {ARDUINO_PORT}: {e}")
    exit()

genius = lyricsgenius.Genius(GENIUS_TOKEN)
genius.remove_section_headers = True 

def fetch_lyrics(title, artist):
    try:
        song = genius.search_song(title, artist)
        if song:
            clean_lyrics = [line.strip() for line in song.lyrics.split('\n') if line.strip()]
            if clean_lyrics:
                clean_lyrics.pop(0) # Strip metadata header line
            return clean_lyrics
    except Exception as e:
        print(f"API Error: {e}")
    return None

current_track = ""
track_lyrics = []
lyric_index = 0

print("\n=== Listener Active: Play a track on Spotify Desktop ===")

while True:
    try:
        active_track = spotify.current()
        track_title = active_track[0]
        track_artist = active_track[1]
        full_track_name = f"{track_title} - {track_artist}"

        if full_track_name != current_track:
            current_track = full_track_name
            print(f"\n🎵 Track Change Detected: {current_track}")
            arduino.write(f"Playing:\n{track_title}\n".encode('utf-8'))
            
            track_lyrics = fetch_lyrics(track_title, track_artist)
            lyric_index = 0
            
            if not track_lyrics:
                arduino.write("Lyrics Not\nFound\n".encode('utf-8'))

        if track_lyrics and lyric_index < len(track_lyrics):
            current_line = track_lyrics[lyric_index]
            print(f"Streaming: {current_line}")
            arduino.write(f"{current_line}\n".encode('utf-8'))
            lyric_index += 1
            time.sleep(4) # Adjust pacing step according to average track tempo
        elif track_lyrics and lyric_index >= len(track_lyrics):
            time.sleep(2)

    except SpotifyNotRunning:
        print("Waiting for Spotify desktop client app launch...", end="\r")
        time.sleep(2)
    except KeyboardInterrupt:
        print("\nProcess terminated by user.")
        break
    except Exception as e:
        print(f"Runtime Exception: {e}")
        time.sleep(2)
