# to get the required packages (ubuntu 21.10):
#   sudo apt install     antlr4 libantlr4-runtime-dev default-jdk
# the ANTLRJAR part below is copied from /usr/bin/antlr4
make --no-print-directory -C ./compiler ANTLRJAR=/usr/share/java/stringtemplate4.jar:/usr/share/java/antlr4.jar:/usr/share/java/antlr4-runtime.jar:/usr/share/java/antlr3-runtime.jar/:/usr/share/java/treelayout.jar ANTLRINC=/usr/include/antlr4-runtime ANTLRLIB=/usr/lib/x86_64-linux-gnu/libantlr4-runtime.a "$@"