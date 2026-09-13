.PHONY: build upload clean monitor check lint test

PIO := uv run pio

build:
	$(PIO) run -e feather

flash:
	$(PIO) run -e feather -t upload

clean:
	$(PIO) run -e feather -t clean

monitor:
	$(PIO) device monitor

check:
	$(PIO) check --skip-packages --src-filters="+<src/>"

test:
	$(PIO) test -e native
