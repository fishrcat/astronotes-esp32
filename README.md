# astronotes-esp32

Fill

## Setup

```sh
curl -LsSf https://astral.sh/uv/install.sh | sh
uv sync
sudo usermod -aG dialout $USER
```

Log out and back in after the `dialout` group change so `make flash` can open `/dev/ttyACM0`.

## Make

| Command | Purpose | Usage |
| --- | --- | --- |
| `make build` | Compile firmware (`pio run`) | |
| `make flash` | Flash the board (`pio run -t upload`) | After flash, join Wi-Fi AP `AstroNotes` and open `http://192.168.4.1`. |
| `make monitor` | Serial monitor (`pio device monitor`) | |
| `make lint` | cppcheck via PlatformIO (`pio check`) | |
| `make clean` | Remove build artifacts (`pio run -t clean`) | |
