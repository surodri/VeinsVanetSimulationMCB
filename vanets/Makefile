#
# OMNeT++/OMNEST Makefile for vanets
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I../veins/src -I../veins/src/veins/base/utils -L../veins/out/$$\(CONFIGNAME\)/src -lveins -KVEINS_PROJ=../veins
#

# Name of target to be created (-o option)
TARGET = vanets$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../veins/src \
    -I../veins/src/veins/base/utils \
    -I. \
    -IDebug \
    -IDebug/out \
    -IDebug/out/gcc-release \
    -IDebug/out/gcc-release/src \
    -IDebug/out/gcc-release/tests \
    -IDebug/out/gcc-release/tests/work \
    -IDebug/out/gcc-release/tests/work/Metrics_NumberOfBits \
    -IDebug/out/gcc-release/tests/work/Metrics_Throughput \
    -IDebug/src \
    -IDebug/tests \
    -IDebug/tests/work \
    -IDebug/tests/work/out \
    -IDebug/tests/work/out/gcc-debug \
    -IDebug/tests/work/out/gcc-debug/Mac1609_4_Metrics \
    -IDebug/tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics \
    -IDebug/tests/work/out/gcc-debug/Metrics_Throughput \
    -IDebug/tests/work/out/gcc-debug/NetworkSimulation_Parameters \
    -IDebug/tests/work/out/gcc-debug/ResultsUtil_Test \
    -Idoc \
    -Idoc/neddoc \
    -Isrc \
    -Isrc/northampton \
    -Isrc/results \
    -Isrc/singlechannel \
    -Itests \
    -Itests/work \
    -Itests/work/out \
    -Itests/work/out/gcc-debug \
    -Itests/work/out/gcc-debug/Mac1609_4_Metrics \
    -Itests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics \
    -Itests/work/out/gcc-debug/Metrics_Throughput \
    -Itests/work/out/gcc-debug/NetworkSimulation_Parameters \
    -Itests/work/out/gcc-debug/ResultsUtil_Test

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../veins/out/$(CONFIGNAME)/src  -lveins
LIBS += -Wl,-rpath,`abspath ../veins/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = $O/src/Mac16094Metrics.o $O/src/Metrics.o $O/src/ResultsUtil.o

# Message files
MSGFILES =

# SM files
SMFILES =

# Other makefile variables (-K)
VEINS_PROJ=../veins

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f vanets vanets.exe libvanets.so libvanets.a libvanets.dll libvanets.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h
	$(Q)-rm -f Debug/*_m.cc Debug/*_m.h Debug/*_sm.cc Debug/*_sm.h
	$(Q)-rm -f Debug/out/*_m.cc Debug/out/*_m.h Debug/out/*_sm.cc Debug/out/*_sm.h
	$(Q)-rm -f Debug/out/gcc-release/*_m.cc Debug/out/gcc-release/*_m.h Debug/out/gcc-release/*_sm.cc Debug/out/gcc-release/*_sm.h
	$(Q)-rm -f Debug/out/gcc-release/src/*_m.cc Debug/out/gcc-release/src/*_m.h Debug/out/gcc-release/src/*_sm.cc Debug/out/gcc-release/src/*_sm.h
	$(Q)-rm -f Debug/out/gcc-release/tests/*_m.cc Debug/out/gcc-release/tests/*_m.h Debug/out/gcc-release/tests/*_sm.cc Debug/out/gcc-release/tests/*_sm.h
	$(Q)-rm -f Debug/out/gcc-release/tests/work/*_m.cc Debug/out/gcc-release/tests/work/*_m.h Debug/out/gcc-release/tests/work/*_sm.cc Debug/out/gcc-release/tests/work/*_sm.h
	$(Q)-rm -f Debug/out/gcc-release/tests/work/Metrics_NumberOfBits/*_m.cc Debug/out/gcc-release/tests/work/Metrics_NumberOfBits/*_m.h Debug/out/gcc-release/tests/work/Metrics_NumberOfBits/*_sm.cc Debug/out/gcc-release/tests/work/Metrics_NumberOfBits/*_sm.h
	$(Q)-rm -f Debug/out/gcc-release/tests/work/Metrics_Throughput/*_m.cc Debug/out/gcc-release/tests/work/Metrics_Throughput/*_m.h Debug/out/gcc-release/tests/work/Metrics_Throughput/*_sm.cc Debug/out/gcc-release/tests/work/Metrics_Throughput/*_sm.h
	$(Q)-rm -f Debug/src/*_m.cc Debug/src/*_m.h Debug/src/*_sm.cc Debug/src/*_sm.h
	$(Q)-rm -f Debug/tests/*_m.cc Debug/tests/*_m.h Debug/tests/*_sm.cc Debug/tests/*_sm.h
	$(Q)-rm -f Debug/tests/work/*_m.cc Debug/tests/work/*_m.h Debug/tests/work/*_sm.cc Debug/tests/work/*_sm.h
	$(Q)-rm -f Debug/tests/work/out/*_m.cc Debug/tests/work/out/*_m.h Debug/tests/work/out/*_sm.cc Debug/tests/work/out/*_sm.h
	$(Q)-rm -f Debug/tests/work/out/gcc-debug/*_m.cc Debug/tests/work/out/gcc-debug/*_m.h Debug/tests/work/out/gcc-debug/*_sm.cc Debug/tests/work/out/gcc-debug/*_sm.h
	$(Q)-rm -f Debug/tests/work/out/gcc-debug/Mac1609_4_Metrics/*_m.cc Debug/tests/work/out/gcc-debug/Mac1609_4_Metrics/*_m.h Debug/tests/work/out/gcc-debug/Mac1609_4_Metrics/*_sm.cc Debug/tests/work/out/gcc-debug/Mac1609_4_Metrics/*_sm.h
	$(Q)-rm -f Debug/tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_m.cc Debug/tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_m.h Debug/tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_sm.cc Debug/tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_sm.h
	$(Q)-rm -f Debug/tests/work/out/gcc-debug/Metrics_Throughput/*_m.cc Debug/tests/work/out/gcc-debug/Metrics_Throughput/*_m.h Debug/tests/work/out/gcc-debug/Metrics_Throughput/*_sm.cc Debug/tests/work/out/gcc-debug/Metrics_Throughput/*_sm.h
	$(Q)-rm -f Debug/tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_m.cc Debug/tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_m.h Debug/tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_sm.cc Debug/tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_sm.h
	$(Q)-rm -f Debug/tests/work/out/gcc-debug/ResultsUtil_Test/*_m.cc Debug/tests/work/out/gcc-debug/ResultsUtil_Test/*_m.h Debug/tests/work/out/gcc-debug/ResultsUtil_Test/*_sm.cc Debug/tests/work/out/gcc-debug/ResultsUtil_Test/*_sm.h
	$(Q)-rm -f doc/*_m.cc doc/*_m.h doc/*_sm.cc doc/*_sm.h
	$(Q)-rm -f doc/neddoc/*_m.cc doc/neddoc/*_m.h doc/neddoc/*_sm.cc doc/neddoc/*_sm.h
	$(Q)-rm -f src/*_m.cc src/*_m.h src/*_sm.cc src/*_sm.h
	$(Q)-rm -f src/northampton/*_m.cc src/northampton/*_m.h src/northampton/*_sm.cc src/northampton/*_sm.h
	$(Q)-rm -f src/results/*_m.cc src/results/*_m.h src/results/*_sm.cc src/results/*_sm.h
	$(Q)-rm -f src/singlechannel/*_m.cc src/singlechannel/*_m.h src/singlechannel/*_sm.cc src/singlechannel/*_sm.h
	$(Q)-rm -f tests/*_m.cc tests/*_m.h tests/*_sm.cc tests/*_sm.h
	$(Q)-rm -f tests/work/*_m.cc tests/work/*_m.h tests/work/*_sm.cc tests/work/*_sm.h
	$(Q)-rm -f tests/work/out/*_m.cc tests/work/out/*_m.h tests/work/out/*_sm.cc tests/work/out/*_sm.h
	$(Q)-rm -f tests/work/out/gcc-debug/*_m.cc tests/work/out/gcc-debug/*_m.h tests/work/out/gcc-debug/*_sm.cc tests/work/out/gcc-debug/*_sm.h
	$(Q)-rm -f tests/work/out/gcc-debug/Mac1609_4_Metrics/*_m.cc tests/work/out/gcc-debug/Mac1609_4_Metrics/*_m.h tests/work/out/gcc-debug/Mac1609_4_Metrics/*_sm.cc tests/work/out/gcc-debug/Mac1609_4_Metrics/*_sm.h
	$(Q)-rm -f tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_m.cc tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_m.h tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_sm.cc tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*_sm.h
	$(Q)-rm -f tests/work/out/gcc-debug/Metrics_Throughput/*_m.cc tests/work/out/gcc-debug/Metrics_Throughput/*_m.h tests/work/out/gcc-debug/Metrics_Throughput/*_sm.cc tests/work/out/gcc-debug/Metrics_Throughput/*_sm.h
	$(Q)-rm -f tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_m.cc tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_m.h tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_sm.cc tests/work/out/gcc-debug/NetworkSimulation_Parameters/*_sm.h
	$(Q)-rm -f tests/work/out/gcc-debug/ResultsUtil_Test/*_m.cc tests/work/out/gcc-debug/ResultsUtil_Test/*_m.h tests/work/out/gcc-debug/ResultsUtil_Test/*_sm.cc tests/work/out/gcc-debug/ResultsUtil_Test/*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc Debug/*.cc Debug/out/*.cc Debug/out/gcc-release/*.cc Debug/out/gcc-release/src/*.cc Debug/out/gcc-release/tests/*.cc Debug/out/gcc-release/tests/work/*.cc Debug/out/gcc-release/tests/work/Metrics_NumberOfBits/*.cc Debug/out/gcc-release/tests/work/Metrics_Throughput/*.cc Debug/src/*.cc Debug/tests/*.cc Debug/tests/work/*.cc Debug/tests/work/out/*.cc Debug/tests/work/out/gcc-debug/*.cc Debug/tests/work/out/gcc-debug/Mac1609_4_Metrics/*.cc Debug/tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*.cc Debug/tests/work/out/gcc-debug/Metrics_Throughput/*.cc Debug/tests/work/out/gcc-debug/NetworkSimulation_Parameters/*.cc Debug/tests/work/out/gcc-debug/ResultsUtil_Test/*.cc doc/*.cc doc/neddoc/*.cc src/*.cc src/northampton/*.cc src/results/*.cc src/singlechannel/*.cc tests/*.cc tests/work/*.cc tests/work/out/*.cc tests/work/out/gcc-debug/*.cc tests/work/out/gcc-debug/Mac1609_4_Metrics/*.cc tests/work/out/gcc-debug/Metrics_PacketsDeliveredToMetrics/*.cc tests/work/out/gcc-debug/Metrics_Throughput/*.cc tests/work/out/gcc-debug/NetworkSimulation_Parameters/*.cc tests/work/out/gcc-debug/ResultsUtil_Test/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/Mac16094Metrics.o: src/Mac16094Metrics.cc \
	src/Mac16094Metrics.h \
	src/Metrics.h \
	$(VEINS_PROJ)/src/veins/base/connectionManager/BaseConnectionManager.h \
	$(VEINS_PROJ)/src/veins/base/connectionManager/ChannelAccess.h \
	$(VEINS_PROJ)/src/veins/base/connectionManager/NicEntry.h \
	$(VEINS_PROJ)/src/veins/base/messages/AirFrame_m.h \
	$(VEINS_PROJ)/src/veins/base/messages/ChannelSenseRequest_m.h \
	$(VEINS_PROJ)/src/veins/base/messages/MacPkt_m.h \
	$(VEINS_PROJ)/src/veins/base/modules/BaseBattery.h \
	$(VEINS_PROJ)/src/veins/base/modules/BaseLayer.h \
	$(VEINS_PROJ)/src/veins/base/modules/BaseMacLayer.h \
	$(VEINS_PROJ)/src/veins/base/modules/BaseMobility.h \
	$(VEINS_PROJ)/src/veins/base/modules/BaseModule.h \
	$(VEINS_PROJ)/src/veins/base/modules/BaseWorldUtility.h \
	$(VEINS_PROJ)/src/veins/base/modules/BatteryAccess.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/AnalogueModel.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/BaseDecider.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/BasePhyLayer.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/ChannelInfo.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/ChannelState.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/Decider.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/DeciderToPhyInterface.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/Interpolation.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/MacToPhyControlInfo.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/MacToPhyInterface.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/Mapping.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/MappingBase.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/MappingUtils.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/PhyToMacControlInfo.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/PhyUtils.h \
	$(VEINS_PROJ)/src/veins/base/phyLayer/Signal_.h \
	$(VEINS_PROJ)/src/veins/base/utils/Coord.h \
	$(VEINS_PROJ)/src/veins/base/utils/FWMath.h \
	$(VEINS_PROJ)/src/veins/base/utils/FindModule.h \
	$(VEINS_PROJ)/src/veins/base/utils/HostState.h \
	$(VEINS_PROJ)/src/veins/base/utils/MiXiMDefs.h \
	$(VEINS_PROJ)/src/veins/base/utils/Move.h \
	$(VEINS_PROJ)/src/veins/base/utils/NetwToMacControlInfo.h \
	$(VEINS_PROJ)/src/veins/base/utils/PassedMessage.h \
	$(VEINS_PROJ)/src/veins/base/utils/SimpleAddress.h \
	$(VEINS_PROJ)/src/veins/base/utils/miximkerneldefs.h \
	$(VEINS_PROJ)/src/veins/modules/analogueModel/JakesFading.h \
	$(VEINS_PROJ)/src/veins/modules/analogueModel/LogNormalShadowing.h \
	$(VEINS_PROJ)/src/veins/modules/analogueModel/SimplePathlossModel.h \
	$(VEINS_PROJ)/src/veins/modules/mac/ieee80211p/Mac1609_4.h \
	$(VEINS_PROJ)/src/veins/modules/mac/ieee80211p/Mac80211pToPhy11pInterface.h \
	$(VEINS_PROJ)/src/veins/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(VEINS_PROJ)/src/veins/modules/messages/Mac80211Pkt_m.h \
	$(VEINS_PROJ)/src/veins/modules/messages/PhyControlMessage_m.h \
	$(VEINS_PROJ)/src/veins/modules/messages/WaveShortMessage_m.h \
	$(VEINS_PROJ)/src/veins/modules/phy/Decider80211p.h \
	$(VEINS_PROJ)/src/veins/modules/phy/Decider80211pToPhy80211pInterface.h \
	$(VEINS_PROJ)/src/veins/modules/phy/DeciderResult80211.h \
	$(VEINS_PROJ)/src/veins/modules/phy/PhyLayer80211p.h \
	$(VEINS_PROJ)/src/veins/modules/phy/SNRThresholdDecider.h \
	$(VEINS_PROJ)/src/veins/modules/utility/Consts80211p.h \
	$(VEINS_PROJ)/src/veins/modules/utility/ConstsPhy.h
$O/src/Metrics.o: src/Metrics.cc \
	src/Metrics.h \
	$(VEINS_PROJ)/src/veins/base/utils/FindModule.h \
	$(VEINS_PROJ)/src/veins/base/utils/MiXiMDefs.h \
	$(VEINS_PROJ)/src/veins/base/utils/miximkerneldefs.h
$O/src/ResultsUtil.o: src/ResultsUtil.cc \
	src/ResultsUtil.h

