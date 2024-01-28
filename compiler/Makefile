# You can override these from the command-line, as illustrated by the various `runmake_*.sh` scripts

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	ANTLRJAR=/usr/local/Cellar/antlr/antlr-4.9.2-complete.jar
	ANTLRINC=/usr/local/include/antlr4-runtime
	ANTLRLIB=/usr/local/lib/antlr/libantlr4-runtime.a
else 
	ANTLRJAR=/usr/share/java/stringtemplate4.jar:/usr/share/java/antlr4.jar:/usr/share/java/antlr4-runtime.jar:/usr/share/java/antlr3-runtime.jar/:/usr/share/java/treelayout.jar
	ANTLRINC=/usr/include/antlr4-runtime
	ANTLRLIB=/usr/lib/x86_64-linux-gnu/libantlr4-runtime.a
endif

CC=g++
CCFLAGS = $(DEBUG) -g -c -std=c++17 -I$(ANTLRINC) -Wno-attributes # -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDFLAGS = $(DEBUG) -g

OBJDIR = build
SRCDIR = src
TREEDIR = tree
GRAMMAR_GENERATED_FILES_DIR = grammar_generated_files

SRC = $(_SRC)
OBJ = $(_OBJ)
DEPENDENCIES = $(_DEPENDENCIES)
APP = ifcc

export

all: generate_files

generate_files : $(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR)
	@$(eval _SRC=$(shell find $(SRCDIR) -name "*.cpp"))
	@$(eval _OBJ=$(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.o))
	@$(eval _DEPENDENCIES=$(SRC:$(SRCDIR)%.cpp=$(OBJDIR)%.d))
	@$(MAKE) $(APP)

##########################################
# generate the C++ implementation of our Lexer/Parser/Visitor
#
# cf https://stackoverflow.com/a/3077254/117814 for the multiple-file trick
$(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR): $(SRCDIR)/ifcc.g4
	@echo "GENERATING VISITOR FILES INTO" $(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR)
	@mkdir -p $(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR)
	@cd $(SRCDIR) && java -cp $(ANTLRJAR) org.antlr.v4.Tool  -visitor -no-listener -Dlanguage=Cpp -o ./$(GRAMMAR_GENERATED_FILES_DIR) ifcc.g4

$(APP): $(OBJ)
	@echo "== LINKING EXECUTABLE $(APP)"
	@$(CC) $(LDFLAGS) $^ $(ANTLRLIB) -o $(OBJDIR)/$(APP)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	@echo "COMPILING SOURCE $< INTO $@"
	@mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -MMD -o $@ $<


# prevent automatic cleanup of "intermediate" files like ifccLexer.cpp etc
.PRECIOUS: $(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR)/ifcc%.cpp   

# automagic dependency management: `gcc -MMD` generates all the .d files for us

-include $(DEPENDENCIES)

##########################################
# view the parse tree in a graphical window

# Usage: `make gui FILE=path/to/your/file.c`
FILE ?= tests/testfiles/01_return42.c

gui:
	@mkdir -p $(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR) $(TREEDIR)
	@cd $(SRCDIR) && java -cp $(ANTLRJAR) org.antlr.v4.Tool -Dlanguage=Java -o $(GRAMMAR_GENERATED_FILES_DIR) ifcc.g4
	@javac -cp $(ANTLRJAR) -d $(TREEDIR) $(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR)/*.java
	@java -cp $(ANTLRJAR):$(TREEDIR) org.antlr.v4.gui.TestRig ifcc axiom -gui ../$(FILE)

##########################################
# delete all machine-generated files
clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(TREEDIR)
	@rm -rf $(SRCDIR)/$(GRAMMAR_GENERATED_FILES_DIR)
	@rm -f ../a.out
	@rm -f ifcc

