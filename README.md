# 🎵 Spotify Real-time Lyrics Streamer to I2C Hardware Display

![Python Version](https://img.shields.io/badge/python-3.10%20%7C%203.13-blue.svg)
![License](https://img.shields.io/badge/License-MPL_2.0-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

A robust, enterprise-grade hardware-software synchronization engine. This project tracks active Spotify playback session state via Web API polling, dynamically extracts metadata, fetches corresponding synchronized lyrics via the Genius API, and streams structured string buffers over Serial protocol to an external I2C hardware character display driven by an Arduino microcontroller.

---

## 📐 System Architecture & Data Flow

```text
 [ Spotify Web Server ]        [ Genius API Server ]
          │                             │
    (Playback Poll)              (Lyrics Fetch)
          ▼                             ▼
   ┌───────────────┐             ┌───────────────┐
   │  spotipy client │ ─────────> │ lyricsgenius  │
   └───────────────┘             └───────────────┘
           │
           │ (Event Loop / Data Cleaning)
           ▼
   ┌─────────────────────────────────────────────┐
   │             Python Controller Core          │
   └─────────────────────────────────────────────┘
           │
           │ (Serial Over USB @ 115200 Baud)
           ▼
   ┌─────────────────────────────────────────────┐
   │         Arduino Hardware Layer              │
   │  (LiquidCrystal_I2C Subsystem @ Addr 0x27)  │
   └─────────────────────────────────────────────┘

```

---

## 🚀 Key Architectural Features

* **Device-Agnostic Session Tracking:** Leverages the official Spotify Web API token subsystem via OAuth 2.0 authorization code flows, intercepting active playback across mobile, web, desktop, or smart speaker clients.
* **Automated Text Normalization:** Strips metadata headers, cleans up Genius embedded analytics tags, and filters non-printable characters dynamically before transmission.
* **Non-Blocking Serial Protocol:** Transmits downstream character arrays at a stable `115200` baud rate with smart line-splitting mechanisms to fit dual-line physical hardware formats (`16x2` matrices).

---

## 🛠️ Hardware Specifications

* **Microcontroller:** Arduino Uno, Nano, or Mega architecture.
* **Peripherals:** 16x2 I2C Character LCD (Optimized for `PCF8574` I2C backpack interface mapped to slave address `0x27`).
* **Bus Topology:** Standard I2C communication bus (`VCC` ── 5V, `GND` ── GND, `SDA` ── A4, `SCL` ── A5 on ATmega328P based devices).

---

## 📦 Software Provisioning

### 1. Embedded Firmware Deployment

1. Initialize the Arduino IDE.
2. Navigate to **Tools** > **Manage Libraries...** and install the **LiquidCrystal I2C** driver suite (authored by Frank de Brabander).
3. Open `spotify_oled_controller.ino`, compile the codebase, and flash the binary payload to your target board.

> **⚠️ Critical Operational Note:** Ensure the Arduino Serial Monitor interface remains completely closed post-flashing. Active monitor instances hook the device descriptor and trigger exclusive lock exceptions (`Access is denied`) inside the Python pipeline.

### 2. Host Environment Setup

1. Clone the repository into your local workspace:
```bash
git clone [https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git)
cd YOUR_REPO_NAME

```


2. Provision project runtime dependencies via the structured requirements manifest:
```bash
pip install -r requirements.txt

```



### 3. API Subsystem Configuration

Generate authentication tokens across both developer interfaces:

* **Genius:** Provision an application client via the [Genius Developer Portal](https://genius.com/api-clients) to generate a bearer token.
* **Spotify:** Register a product entry on the [Spotify Developer Dashboard](https://developer.spotify.com/dashboard). You **must** configure the **Redirect URI** whitelist value exactly to `https://localhost:8888/callback`. Take note of the `Client ID` and `Client Secret`.

Inject your specific keys into the `song.py` configuration controller block:

```python
# === CONFIGURATION SUBSYSTEM ===
GENIUS_TOKEN = "YOUR_GENIUS_API_TOKEN"
ARDUINO_PORT = 'COM3'  # Update port mapping target per your OS hardware assignment
BAUD_RATE = 115200

SPOTIPY_CLIENT_ID = "YOUR_SPOTIFY_CLIENT_ID"
SPOTIPY_CLIENT_SECRET = "YOUR_SPOTIFY_CLIENT_SECRET"
SPOTIPY_REDIRECT_URI = "https://localhost:8888/callback"
# ===============================

```

---

## 🏃 Execution Protocol

1. Interface your Arduino device with the host computer using a dedicated USB bridge cable.
2. Initialize the Python host orchestrator script:
```bash
python song.py

```


3. *Initial Authorization Routine:* During the first bootstrap execution, a secure OAuth login screen will manifest in your default web browser. Click **Agree** to authorize scope access. Upon redirection to the local loopback server (`https://localhost:8888/callback?...`), copy the **entire URL payload string** from your address bar and paste it directly into the terminal prompt.
4. Initiate any media playback session within your Spotify account. The data engine will stream cleaned lyrics synchronously to your external hardware peripheral.

---

## 🛡️ Open Source Licensing

This project is licensed under the **Mozilla Public License 2.0 (MPL-2.0)**.

Source code modification and integration rules apply according to the standard MPL-2.0 copyleft terms. A complete legal copy of the license is provided in the accompanying [LICENSE](https://www.google.com/search?q=LICENSE) file located within the root directory of this repository.

```

---kamu sekarang sudah setara dengan standar proyek *open-source* profesional.

```
