#!/bin/bash
mkdir -vp build/{m4,aux,ui} || exit $?
autoreconf -vfi
