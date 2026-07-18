# 🎵 Spotify Real-time Lyrics Streamer to I2C Hardware Display

A smart hardware-software integration that tracks your active Spotify playback in real-time, automatically fetches the matching song lyrics via the Genius API, and streams them line-by-line onto an external I2C hardware display connected to an Arduino.

---

## 🚀 Features
- **Device-Agnostic Real-time Tracking:** Utilizes the official Spotify Web API (`spotipy`) to catch track changes instantly, whether you play music from your desktop, mobile, or web player.
- **Automated Lyrics Fetching:** Integrates with the Genius API (`lyricsgenius`) to dynamically source and clean up song lyrics on the fly.
- **Robust Serial Communication:** Streams data smoothly over a USB Serial interface at 115200 baud rate with custom data-handling logic to prevent buffer overflows.
- **Clean Hardware Output:** Automatically formats and wraps long lyric lines to fit dual-line character displays perfectly.

---

## 🛠️ Hardware Requirements
- **Microcontroller:** Arduino Uno, Nano, or Mega.
- **Display:** 16x2 I2C Character LCD (or compatible I2C display running on address `0x27`).
- **Wiring:** 4x Jumper wires (VCC to 5V, GND to GND, SDA to A4, SCL to A5 on standard Uno).

---

## 📦 Software Setup

### 1. Hardware Initialization
1. Open the Arduino IDE.
2. Go to **Tools** > **Manage Libraries...** and install the **LiquidCrystal I2C** library (by Frank de Brabander / Marco Schwartz).
3. Open `spotify_oled_controller.ino` from this project, verify the configuration, and upload it to your board.
> **Note:** Make sure to close the Arduino Serial Monitor after uploading, as it will otherwise block the Python script from accessing the COM port.

### 2. Python Environment Setup
1. Clone this repository to your local machine:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git)
   cd YOUR_REPO_NAME

```

2. Install all required dependencies using `pip`:
```bash
pip install -r requirements.txt

```



### 3. API Credentials Configuration

To establish a secure connection, you need to grab tokens from both platform dashboards:

* **Genius:** Create an API client at [Genius Developers](https://genius.com/api-clients) to obtain your access token.
* **Spotify:** Head over to the [Spotify Developer Dashboard](https://developer.spotify.com/dashboard), create an application, and set the **Redirect URI** strictly to `https://localhost:8888/callback`. Copy your `Client ID` and `Client Secret`.

Open `song.py` and input your keys inside the configuration block:

```python
# === CONFIGURATION SUBSYSTEM ===
GENIUS_TOKEN = "YOUR_GENIUS_API_TOKEN"
ARDUINO_PORT = 'COM3'  # Update to match your actual Arduino port
BAUD_RATE = 115200

SPOTIPY_CLIENT_ID = "YOUR_SPOTIFY_CLIENT_ID"
SPOTIPY_CLIENT_SECRET = "YOUR_SPOTIFY_CLIENT_SECRET"
SPOTIPY_REDIRECT_URI = "https://localhost:8888/callback"
# ===============================

```

---

## 🏃 Running the Application

1. Connect your Arduino to your computer via USB.
2. Fire up the Python automation script:
```bash
python song.py

```


3. *First-time run only:* A browser window will pop up prompting you to log into Spotify and authorize the app. Once accepted, you will be redirected to a blank URL starting with `https://localhost:8888/callback...`. **Copy the entire URL from your browser address bar and paste it into your terminal.**
4. Play any track on your Spotify app and watch the lyrics stream onto your hardware display completely hands-free!

```
---

## 🤝 Open Source Contributions

Contributions, feature optimization pull requests, and forks are warmly welcomed! Feel free to raise an issue if you want to request feature changes.

## 📄 Licensing Terms

This system structure deployment framework is published under the **Mozilla Public License 2.0 (MPL 2.0)**. For complete documentation terms, review the local `LICENSE` file.

---
