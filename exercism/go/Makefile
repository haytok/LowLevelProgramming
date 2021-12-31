IMAGE_NAME=exercism-go

.PHONY: build
dev-build:
	docker build -t $(IMAGE_NAME) .

.PHONY: run
run:
	docker run --rm \
		--name $(IMAGE_NAME) \
		-v $(PWD):/go/src/app \
		-it $(IMAGE_NAME) \
		/bin/sh
