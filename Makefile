# Makefile
# Tobit Flatscher - github.com/2b-t (2020)

# Compiler settings: ICC or GCC (alternatively: 'export COMPILER=ICC' in console)
COMPILER = GCC

# Define sub-directories to be included in compilation
SRCDIR  = src
OBJDIR  = obj
BINDIR  = bin
REQDIRS = backup output/bin output/vtk

SOURCES  = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
INCLUDES = $(wildcard $(SRCDIR)/*.hpp) $(wildcard $(SRCDIR)/*/*.hpp)
OBJECTS  = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
PROGRAM	 = main.$(COMPILER)

# Compiler flags
WARNINGS   = -Wall -pedantic -Wextra -Weffc++ -Woverloaded-virtual  -Wfloat-equal -Wshadow -Wredundant-decls -Winline -fmax-errors=1
CXXFLAGS  += -std=c++17 -O3 -flto -funroll-all-loops -finline-functions -mavx2 -march=native -DNDEBUG
LINKFLAGS += -O3 -flto

# Compiler settings for specific compiler
ifeq ($(COMPILER),ICC)
	# Intel compiler ICC
	CXX        = icpc
	LINKER     = icpc
	CXXFLAGS  += -fopenmp
	LINKFLAGS += -qopenmp
	COMPILER   = ICC
else
	# Gnu compiler GCC
	CXX        = g++
	LINKER     = g++
	CXXFLAGS  += -fopenmp
	LINKFLAGS += -lgomp
	COMPILER   = GCC
endif

# Make commands
default: $(BINDIR)/$(PROGRAM)

$(BINDIR)/$(PROGRAM): $(OBJECTS)
	@mkdir -p $(REQDIRS)
	@mkdir -p $(@D)
	$(LINKER)  $(OBJECTS)  $(LINKFLAGS) -o $@
	@echo "Linking complete!"
	
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@rm -f $(BINDIR)/$(PROGRAM) $(OBJECTS)

run: clean $(BINDIR)/$(PROGRAM)
	./$(BINDIR)/$(PROGRAM)

doc:
	doxygen Doxyfile

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

info:
	@echo "Show optimization flags"
	$(CXX) --version
	@echo $(CXXFLAGS)
