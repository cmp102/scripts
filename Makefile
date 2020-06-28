SCRIPTS=brightness setbg volume getProgressString sshot sw
BINARIES=battery progress
SCRIPTS += $(BINARIES)

PREFIX=/usr/local

BINDIR=$(PREFIX)/bin/

SCRIPTSBIN = $(addprefix $(BINDIR),$(SCRIPTS))

CCBATFLAGS=-I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lpthread -lnotify -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

CCFLAGS=-Wall -O3

binaries: $(BINARIES)

battery: battery.c
	$(CC) $(CCBATFLAGS) $(CCFLAGS) battery.c -o battery

progress: progress.c
	$(CC) $(CCFLAGS) progress.c -o progress

clean:
	rm $(BINARIES)

install: $(SCRIPTSBIN)
	@echo $(SCRIPTS) installed

$(BINDIR)%: % $(BINDIR)
	cp $< $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

uninstall:
	rm -f $(SCRIPTSBIN)

options:
	@echo PREFIX: $(PREFIX)
	@echo SCRIPTS: $(SCRIPTS)

.PHONY: install uninstall binaries

