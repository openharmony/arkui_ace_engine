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

SRC_PATH       = "./"
SRC_PATH_PRODUCTION = ""

SRCSTS = \
	tests/uipluginComputed.ts \
	tests/uipluginComputedParams.ts \
	tests/uipluginStateSimple.ts \
	tests/uipluginState.ts \
	tests/uipluginObservedObject3.ts \
	tests/uipluginAppStorageV2.ts \
	tests/uipluginAppStorageV2simple.ts \
	tests/uipluginPersistentStorageV2.ts \
	tests/uipluginPersistentStorageV2simple.ts \
	tests/uipluginUiUtils.ts \
	\
	decorator.ts \
	utils.ts \
	tests/main.ts \
	tests/test.ts \
	tests/lib/testFramework.ts  \
	tests/lib/testAddRefFireChange.ts \
	tests/lib/stateTracker.ts \
	\
	base/backingValue.ts \
	base/iBackingValue.ts \
	base/iFactoryInternal.ts \
	base/mutableStateMeta.ts \
	base/observeSingleton.ts \
    base/observeWrappedArray.ts \
	base/observeWrappedBase.ts \
	base/observeWrappedDate.ts \
	base/observeWrappedMap.ts \
	base/observeWrappedSet.ts \
	base/stateMgmtFactory.ts \
	base/stateUpdateLoop.ts \
	\
	base/types.ts \
	base/uiUtilsImpl.ts \
	\
	mock/contextConstant.ts \
	mock/extendableComponent.ts \
	mock/factoryInternal.ts \
	mock/ani_storage_mock.ts \
	mock/env_mock.ts  \
	mock/interop.ts  \
	mock/UIContextUtil.ts  \
	mock/interopStorageV2.ts \
	\
	interop/interopStorage.ts \
	\
	decoratorImpl/decoratorBase.ts \
	decoratorImpl/decoratorComputed.ts \
	decoratorImpl/decoratorConsume.ts \
	decoratorImpl/decoratorConsumer.ts \
	decoratorImpl/decoratorLink.ts \
	decoratorImpl/decoratorLocal.ts \
	decoratorImpl/decoratorMonitor.ts \
	decoratorImpl/decoratorObjectLink.ts \
	decoratorImpl/decoratorParam.ts \
	decoratorImpl/decoratorParamOnce.ts \
	decoratorImpl/decoratorProp.ts \
	decoratorImpl/decoratorPropRef.ts \
	decoratorImpl/decoratorProvide.ts \
	decoratorImpl/decoratorProvider.ts \
	decoratorImpl/decoratorState.ts \
	decoratorImpl/decoratorStorageLink.ts \
	decoratorImpl/decoratorStorageProp.ts \
	decoratorImpl/decoratorStoragePropRef.ts \
	decoratorImpl/decoratorWatch.ts \
	\
	storage/appStorage.ts \
	storage/appStorageV2.ts \
	storage/localStorage.ts \
	storage/persistenceV2.ts \
	storage/persistentStorage.ts \
	storage/storageBase.ts \
	storage/storageProperty.ts \
	\
	tools/stateMgmtDFX.ts \
	tools/arkts/stateMgmtTool.ts \
	tools/arkts/observeInterfaceProxy.ts

OBJSTS           = $(patsubst %.ts,${TARGET_PATH}/%.abc,$(SRCSTS))

# Special framework build source (exclude test and uiPlugin subdirs)
FRAMEWORK_SRCS = $(shell find ${SRC_PATH} \
	\( -path utest \) -prune -o \
	\( -name '*.ets' -print \))
FRAMEWORK_OBJS = $(patsubst ${SRC_PATH}/%.ets,${TARGET_PATH}/%.abc,$(FRAMEWORK_SRCS))
FRAMEWORK_TARGET = ${TARGET_PATH}/framework.abc

# Config entry function of program
ENTRY          = main.ETSGLOBAL::main

run: $(TARGET)
	@${LAUNCHER} ${LAUNCH_FLAGS} --panda-files $(TARGET) $(TARGET) ${ENTRY}

$(TARGET): ${OBJSTS}
	echo "*** TARGET - OBJ STS ***"
	@echo "    linking $@ ..."
	@${LINKER} --output=$@ -- ${OBJSTS}

${TARGET_PATH}/%.abc: ${SRC_PATH}/%.ets
	echo "File  EST -> ABC " $<
	@mkdir -p $(dir $@)
	@echo "    compiling $< ..."
	@${COMPILER} ${COMPILE_FLAGS} --output=$@ $<

${TARGET_PATH}/%.abc: %.ts
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

all: run

.PHONY: all clean run framework