# Config panda path
ARCH           = $(shell [ $$(uname -p) = "aarch64" ] && echo arm64_)
PANDA_SDK      = node_modules/@panda/sdk
PANDA_ARCH_BIN = ${PANDA_SDK}/linux_${ARCH}host_tools/bin

# Config command
COMPILER       = ${PANDA_ARCH_BIN}/es2panda
LINKER         = ${PANDA_ARCH_BIN}/ark_link
LAUNCHER       = ${PANDA_ARCH_BIN}/ark

# Config compile and launch flags
COMPILE_FLAGS  = --arktsconfig=./arktsconfig.json
COMPILETS_FLAGS  = --arktsconfig=./arktsconfig.json --extension=ets
LAUNCH_FLAGS   = --load-runtimes=ets --boot-panda-files=${PANDA_SDK}/ets/etsstdlib.abc

# Config target
TARGET_PATH    = output
TARGET         = ${TARGET_PATH}/output.abc

SRC_PATH       = src
SRC_PATH_PRODUCTION = frameworks
SRCS           = $(shell find ${SRC_PATH} ! -wholename src/stateManagement/index.ets -type f -name '*.ets')
SRCSTS1        = $(shell find ${SRC_PATH_PRODUCTION}  -type f -name '*.ts')
SRCSTS = 	tests/main.ts
OBJS           = $(patsubst ${SRC_PATH}/%.ets,${TARGET_PATH}/%.abc,$(SRCS))
OBJSTS           = $(patsubst ${SRC_PATH_PRODUCTION}/%.ts,${TARGET_PATH}/%.abc,$(SRCSTS))

# Special framework build source (exclude test and uiPlugin subdirs)
FRAMEWORK_SRCS = $(shell find ${SRC_PATH} \
	\( -path utest \) -prune -o \
	\( -name '*.ets' -print \))
FRAMEWORK_OBJS = $(patsubst ${SRC_PATH}/%.ets,${TARGET_PATH}/%.abc,$(FRAMEWORK_SRCS))
FRAMEWORK_TARGET = ${TARGET_PATH}/framework.abc

# Config entry function of program
ENTRY          = main.ETSGLOBAL::main

test:
	echo "*** test ***"
	@echo "🔁 Changing private to public for Unit testing"
	@echo "🔁 Adding import for StateTracker to mutableStateMeta.ets"
	@sed -i "/import { stateMgmtConsole } from 'stateManagement\/tools\/stateMgmtConsoleTrace'/a import { StateTracker } from 'stateManagement/utest/lib/stateTracker';" ./src/stateManagement/base/mutableStateMeta.ets
	@echo "🔁 Adding StateTracker calls to mutableStateMeta.ets"
	@sed -i "/this.__metaDependency!.value;/a StateTracker.increaseRefCnt();" ./src/stateManagement/base/mutableStateMeta.ets
	@sed -i "/this.__metaDependency!.value += 1;/a StateTracker.increaseFireChangeCnt();" ./src/stateManagement/base/mutableStateMeta.ets
	@sed -i "/metaDependency.addRef();/a StateTracker.increaseRefCnt();" ./src/stateManagement/base/mutableStateMeta.ets
	@sed -i "/metaDependency.fireChange();/a StateTracker.increaseFireChangeCnt();" ./src/stateManagement/base/mutableStateMeta.ets

	@bash -c " \
		set -e; \
		trap '\
			echo 🔁 Restoring original code...; \
			echo 🔁 Removing all lines with StateTracker from mutableStateMeta.ets...; \
			sed -i \"/StateTracker/d\" ./src/stateManagement/base/mutableStateMeta.ets; \
		' EXIT; \
		echo 🚀 Running test...; \
		make $(TARGET); \
		${LAUNCHER} ${LAUNCH_FLAGS} --panda-files $(TARGET) $(TARGET) ${ENTRY}; \
	"

run: $(TARGET)
	@${LAUNCHER} ${LAUNCH_FLAGS} --panda-files $(TARGET) $(TARGET) ${ENTRY}

$(TARGET): ${OBJSTS}
	echo "*** TARGET - OBJ ***"
	@echo "    linking $@ ..."
	@${LINKER} --output=$@ -- ${OBJS}  ${OBJSTS}

${TARGET_PATH}/%.abc: ${SRC_PATH}/%.ets
	echo "File  EST -> ABC " $<
	@mkdir -p $(dir $@)
	@echo "    compiling $< ..."
	@${COMPILER} ${COMPILE_FLAGS} --output=$@ $<

${TARGET_PATH}/%.abc: ${SRC_PATH_PRODUCTION}/%.ts
	echo "File TS -> ABC " $<
	@mkdir -p $(dir $@)
	@echo "    compiling $< ..."
	@${COMPILER} ${COMPILETS_FLAGS} --output=$@ $<

# Build only the framework (excluding utest)
framework: $(FRAMEWORK_TARGET)
	echo "*** framework  $(FRAMEWORK_TARGET) *** $(FRAMEWORK_TARGET)"

$(FRAMEWORK_TARGET): ${FRAMEWORK_OBJS}
	@echo "    linking $@ ..."
	@${LINKER} --output=$@ -- ${FRAMEWORK_OBJS}

clean:
	@rm -rf ${TARGET_PATH}

all: test

.PHONY: all clean run framework