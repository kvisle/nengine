SUBDIRS = lib src

NENGINE       = nengine$(EXEEXT)

CLEANFILES = $(NENGINE)

EXTRA_DIST = autogen.sh include

all-local: $(NENGINE)

$(NENGINE):
	$(LN_S) "src/$(NENGINE)" "$(NENGINE)"

