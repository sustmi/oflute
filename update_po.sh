#!/bin/sh
./make_pot.sh

msgmerge -s -U po/es.po po/oflute.pot
msgmerge -s -U po/en.po po/oflute.pot
