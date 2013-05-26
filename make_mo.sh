#!/bin/sh

echo "* Generating es.mo..."
mkdir -p lang/es/LC_MESSAGES
msgfmt -c -v -o lang/es/LC_MESSAGES/oflute.mo po/es.po

echo "* Generating en.mo..."
mkdir -p lang/en/LC_MESSAGES
msgfmt -c -v -o lang/en/LC_MESSAGES/oflute.mo po/en.po
