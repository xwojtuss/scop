#!/bin/bash

cd "$(dirname "$0")/.." || exit 1

export PLANTUML_LIMIT_SIZE=32768

hpp2plantuml -i $(find srcs -name '*.hpp' | tr '\n' ' ' | replace ' ' ' -i ' | head -c -4) -o ./docs/plantuml.txt \
    && java -jar ~/.java/plantuml-*.jar -tsvg ./docs/plantuml.txt \
    && java -jar ~/.java/plantuml-*.jar -tpng ./docs/plantuml.txt
