<div align="center">

# 🎵 Spotify Real-Time Lyrics Streamer

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Arduino_Uno-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino">
  <img src="https://img.shields.io/badge/Language-Python_3-3776AB?style=for-the-badge&logo=python&logoColor=white" alt="Python">
  <img src="https://img.shields.io/badge/Service-Spotify-1DB954?style=for-the-badge&logo=spotify&logoColor=white" alt="Spotify">
  <img src="https://img.shields.io/badge/License-MPL_2.0-red?style=for-the-badge" alt="License">
</p>

---

### 🌟 Bring Your Desktop Music to Life
An elegant IoT hardware-software bridge that hooks into your **Spotify Desktop client**, fetches dynamic, cleaned lyrics via the **Genius API**, and streams them seamlessly onto an **I2C OLED Display** powered by an **Arduino Uno**.

[✨ Features](#-key-features) • [📂 Structure](#-repository-architecture) • [🔌 Wiring](#-hardware-wiring) • [🚀 Getting Started](#-installation--setup)

</div>

---

## ⚡ Key Features

* 🚀 **Instant Track Sync** — Seamlessly detects song updates on your desktop app within milliseconds.
* 📝 **Automated Lyric Fetching** — Automatically isolates and formats lyric strings from Genius API.
* 📟 **Optimized Text Buffer** — Handles layout margins and clear-screen buffers natively on the OLED panel.
* ⚡ **High-Speed Serial Bridge** — Fast data pipeline streaming via standard USB Serial at `115200 baud`.

---

## 📂 Repository Architecture

```text
spotify-oled-lyrics/
├── .gitignore
├── LICENSE
├── README.md
├── requirements.txt
├── src/
│   └── spotify_to_arduino.py       # Host Core Logic (Python)
└── firmware/
    └── spotify_lyrics/
        └── spotify_lyrics.ino      # Embedded Device Firmware (C++)
🛠️ System Workflow┌──────────────────┐               ┌──────────────────────┐
│ Spotify Desktop  │ ──(Session)─> │ Python Service (src) │
└──────────────────┘               └──────────┬───────────┘
                                              │ (Genius API Fetch)
                                              ▼
┌──────────────────┐               ┌──────────────────────┐
│ OLED Panel (I2C) │ <───(Bus)──── │ Arduino Uno (firm)   │ <──(USB Serial)
└──────────────────┘               └──────────────────────┘
🎛️ Tech StackMicrocontroller: Arduino Uno R3 (ATmega328P architecture)Display Panel: SSD1306 0.96" I2C OLED Screen (128x64 pixels)Host Engine: Python 3.8+ Background Pipeline🔌 Hardware WiringOLED PinsArduino PinsFunctionWire Color (Rec.)VCC5V / 3.3VPower Interface🔴 RedGNDGNDCommon Ground Connection⚫ BlackSCLA5 / SCLI2C Hardware Serial Clock🟡 YellowSDAA4 / SDAI2C Hardware Serial Data🟢 Green🚀 Installation & Setup📦 1. Firmware InitializationLaunch the Arduino IDE.Press Ctrl+Shift+I to open the Library Manager, then install:Adafruit SSD1306Adafruit GFX LibraryOpen firmware/spotify_lyrics/spotify_lyrics.ino and Upload it to the Uno.Go to Tools > Port and make sure to copy your connection port (e.g., COM3).🔑 2. API Credentials ConfigurationHead over to the Genius Developer Portal.Create a new client token workspace with these configurations:App Name: Spotify-OLED-StreamerApp Website URL: https://github.comRedirect URI: http://localhostHit Save and extract your premium Client Access Token.💻 3. Environment IntegrationOpen up your preferred CLI prompt at the root project workspace directory.Install standard framework dependencies:Bashpip install -r requirements.txt
Open src/spotify_to_arduino.py and inject your active configuration properties:PythonGENIUS_TOKEN = "YOUR_GENIUS_ACCESS_TOKEN_HERE"
ARDUINO_PORT = "COM3"  # Change to your mapped serial port
🏃 Execution PathInterface your hardware assembly unit safely into the host PC terminal slot.Start up the Spotify Desktop Client app and play a track.Trigger the data engine script directly from your terminal:Bashpython src/spotify_to_arduino.py
Watch the hardware terminal flip smoothly from "Awaiting Spotify..." straight into the real-time lryics feed.⚠️ Scope & ConstraintsSerial Link Dependency: The ATmega328P lacks built-in Wi-Fi adapters. The device requires an ongoing USB physical tether connection link to stay updated.Scroll Speed Tuning: Pacing intervals are configured by a basic linear baseline delay timer via time.sleep(4). You can adjust this value anytime to dynamically calibrate the scroll cadence against the average rhythm of your favorite playlist.🤝 Open Source ContributionsContributions, feature optimization pull requests, and forks are warmly welcomed! Feel free to raise an issue if you want to request feature changes.📄 Licensing TermsThis system structure deployment framework is published under the Mozilla Public License 2.0 (MPL 2.0). For complete documentation terms, review the local LICENSE file.
