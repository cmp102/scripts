SCRIPTS = brightness setbg volume getProgressString sshot

PREFIX=/usr/local

BINDIR=$(PREFIX)/bin/

SCRIPTSBIN = $(addprefix $(BINDIR),$(SCRIPTS))

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

.PHONY: install uninstall

