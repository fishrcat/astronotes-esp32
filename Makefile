.PHONY: build upload clean monitor lint

PIO := uv run pio

build:
	$(PIO) run

flash:
	$(PIO) run -t upload

clean:
	$(PIO) run -t clean

monitor:
	$(PIO) device monitor

lint:
	$(PIO) check --skip-packages --src-filters="+<src/>"
