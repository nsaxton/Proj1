#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CApp.o \
	${OBJECTDIR}/CAquarium.o \
	${OBJECTDIR}/CCatfish.o \
	${OBJECTDIR}/CCountFishVisitor.o \
	${OBJECTDIR}/CDecorBubbleTreasure.o \
	${OBJECTDIR}/CDecorTreasure.o \
	${OBJECTDIR}/CFish.o \
	${OBJECTDIR}/CFishBeta.o \
	${OBJECTDIR}/CFishSparty.o \
	${OBJECTDIR}/CFishVisitor.o \
	${OBJECTDIR}/CFrame.o \
	${OBJECTDIR}/CItem.o \
	${OBJECTDIR}/CItemVisitor.o \
	${OBJECTDIR}/CReporter.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/CApp.o: CApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CApp.o CApp.cpp

${OBJECTDIR}/CAquarium.o: CAquarium.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CAquarium.o CAquarium.cpp

${OBJECTDIR}/CCatfish.o: CCatfish.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CCatfish.o CCatfish.cpp

${OBJECTDIR}/CCountFishVisitor.o: CCountFishVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CCountFishVisitor.o CCountFishVisitor.cpp

${OBJECTDIR}/CDecorBubbleTreasure.o: CDecorBubbleTreasure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDecorBubbleTreasure.o CDecorBubbleTreasure.cpp

${OBJECTDIR}/CDecorTreasure.o: CDecorTreasure.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDecorTreasure.o CDecorTreasure.cpp

${OBJECTDIR}/CFish.o: CFish.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFish.o CFish.cpp

${OBJECTDIR}/CFishBeta.o: CFishBeta.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFishBeta.o CFishBeta.cpp

${OBJECTDIR}/CFishSparty.o: CFishSparty.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFishSparty.o CFishSparty.cpp

${OBJECTDIR}/CFishVisitor.o: CFishVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFishVisitor.o CFishVisitor.cpp

${OBJECTDIR}/CFrame.o: CFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFrame.o CFrame.cpp

${OBJECTDIR}/CItem.o: CItem.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CItem.o CItem.cpp

${OBJECTDIR}/CItemVisitor.o: CItemVisitor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CItemVisitor.o CItemVisitor.cpp

${OBJECTDIR}/CReporter.o: CReporter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CReporter.o CReporter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/proj1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
