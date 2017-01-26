FOLDERS=poneyserver
.PHONY: all $(FOLDERS)
all: $(FOLDERS)
poneyserver:
	make -C poneyserver
