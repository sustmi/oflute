#!/bin/sh
VERSION=0.1
echo "* Initial pot file..."
xgettext --package-name oflute --package-version $VERSION --default-domain oflute --output po/oflute.pot --from-code=utf-8 --copyright-holder="José Tomás Tocino García <theom3ga@gmail.com>" --msgid-bugs-address="theom3ga@gmail.com" -s -k_ -C ./src/*.cpp

# msginit -l es -o po/es.po -i po/oflute.pot
# msginit -l en -o po/en.po -i po/oflute.pot
