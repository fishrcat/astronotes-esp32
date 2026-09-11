.PHONY: build upload clean monitor check lint

PIO := uv run pio

build:
	$(PIO) run

flash:
	$(PIO) run -t upload

clean:
	$(PIO) run -t clean

monitor:
	$(PIO) device monitor

check:
	$(PIO) check --skip-packages --src-filters="+<src/>"
