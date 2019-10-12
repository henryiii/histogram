from __future__ import print_function, division

import os
import sys
import re
import glob

try:
    from pathlib import Path
except ImportError:

    # Drop when Python2 support is dropped
    class Path(str):
        def __new__(cls, path):
            return super(cls, Path).__new__(cls, os.path.normpath(path))

        def __truediv__(self, s):
            return self.__class__(os.path.join(self, s))

        def resolve(self):
            return self.__class__(os.path.abspath(self))

        def relative_to(self, other):
            return self.__class__(os.path.relpath(self, other))

        def glob(self, ex):  # Warning: hacky workaround - returns all files
            for root, _, files in os.walk(self):
                for f in files:
                    yield self.__class__(root) / f

        @property
        def parent(self):
            return self.__class__(os.path.dirname(self))


this_path = Path(__file__).resolve().parent

include_path = this_path.parent / "include"
all_headers = {f.relative_to(include_path) for f in include_path.glob("**/*.hpp")}


def get_headers(filename):
    with open(str(filename)) as f:
        for hdr in re.findall('^#include [<"]([^>"]+)[>"]', f.read(), re.MULTILINE):
            if hdr.startswith("boost/histogram"):
                yield Path(hdr)


included_headers = set()
unread_headers = set(get_headers(this_path / "odr_test.cpp"))

while unread_headers:
    included_headers.update(unread_headers)
    for hdr in tuple(unread_headers):
        unread_headers.remove(hdr)
        for hdr2 in get_headers(include_path / hdr):
            if hdr2 not in included_headers:
                unread_headers.add(hdr2)

print("Checked", len(all_headers), "headers")

diff = sorted(all_headers - included_headers)

if diff:
    print("Header not included in odr_test.cpp:")
    for fn in diff:
        print(fn)

sys.exit(len(diff))
