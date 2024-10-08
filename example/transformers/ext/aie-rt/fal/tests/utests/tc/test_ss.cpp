// Copyright(C) 2020 - 2021 by Xilinx, Inc. All rights reserved.
// SPDX-License-Identifier: MIT

#include "xaiefal/xaiefal.hpp"

#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include "CppUTest/TestRegistry.h"

#include "common/tc_config.h"

using namespace std;
using namespace xaiefal;

TEST_GROUP(StreamSelect)
{
};

TEST(StreamSelect, SSBasic) {
	AieRC RC;
	std::vector<XAie_LocType> vL, vL1;
	XAie_Events SSEvent;

	uint32_t SSRscType;

	XAie_ModuleType StartM, EndM, StartM1, EndM1;

	XAie_SetupConfig(ConfigPtr, HW_GEN, XAIE_BASE_ADDR,
			XAIE_COL_SHIFT, XAIE_ROW_SHIFT,
			XAIE_NUM_COLS, XAIE_NUM_ROWS, XAIE_SHIM_ROW,
			XAIE_MEM_TILE_ROW_START, XAIE_MEM_TILE_NUM_ROWS,
			XAIE_AIE_TILE_ROW_START, XAIE_AIE_TILE_NUM_ROWS);

	XAie_InstDeclare(DevInst, &ConfigPtr);

	RC = XAie_CfgInitialize(&(DevInst), &ConfigPtr);
	CHECK_EQUAL(RC, XAIE_OK);

	auto Aie = std::make_shared<XAieDev>(&DevInst, true);
	auto Stream = Aie->tile(1,3).sswitchPort();

	RC = Stream->getSSIdleEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_ERR);

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, CORE, 0);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->reserve();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSIdleEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSRunningEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSStalledEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSTlastEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->release();
	CHECK_EQUAL(RC, XAIE_OK);

	/*Test reserve with preferred resource Id*/
	RC = Stream->setPreferredId(1);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->reserve();
	CHECK_EQUAL(RC, XAIE_OK);

	SSRscType = Stream->getRscType();

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, CORE, 0);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->release();
	CHECK_EQUAL(RC, XAIE_OK);

}

TEST(StreamSelect, SSNegative) {
	AieRC RC;
	std::vector<XAie_LocType> vL, vL1;
	XAie_Events SSEvent;

	uint32_t SSRscType;

	XAie_ModuleType StartM, EndM, StartM1, EndM1;

	XAie_SetupConfig(ConfigPtr, HW_GEN, XAIE_BASE_ADDR,
			XAIE_COL_SHIFT, XAIE_ROW_SHIFT,
			XAIE_NUM_COLS, XAIE_NUM_ROWS, XAIE_SHIM_ROW,
			XAIE_MEM_TILE_ROW_START, XAIE_MEM_TILE_NUM_ROWS,
			XAIE_AIE_TILE_ROW_START, XAIE_AIE_TILE_NUM_ROWS);

	XAie_InstDeclare(DevInst, &ConfigPtr);

	RC = XAie_CfgInitialize(&(DevInst), &ConfigPtr);
	CHECK_EQUAL(RC, XAIE_OK);

	auto Aie = std::make_shared<XAieDev>(&DevInst, true);
	auto Stream = Aie->tile(1,3).sswitchPort();

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, CORE, 0);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSIdleEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_ERR);

	DevInst.IsReady = 1;

	RC = Stream->reserve();
	CHECK_EQUAL(RC, XAIE_OK);

	DevInst.IsReady = 0;

	RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_INVALID_ARGS);

	DevInst.IsReady = 1;

	RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, CORE, 0);
	CHECK_EQUAL(RC, XAIE_ERR);

	DevInst.IsReady = 0;

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_INVALID_ARGS);

	DevInst.IsReady = 1;

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->release();
	CHECK_EQUAL(RC, XAIE_OK);

}

#if AIE_GEN != 1
TEST(StreamSelect, SSBasicMemTile) {
	AieRC RC;
	std::vector<XAie_LocType> vL, vL1;
	XAie_Events SSEvent;

	uint32_t SSRscType;

	XAie_ModuleType StartM, EndM, StartM1, EndM1;

	XAie_SetupConfig(ConfigPtr, HW_GEN, XAIE_BASE_ADDR,
			XAIE_COL_SHIFT, XAIE_ROW_SHIFT,
			XAIE_NUM_COLS, XAIE_NUM_ROWS, XAIE_SHIM_ROW,
			XAIE_MEM_TILE_ROW_START, XAIE_MEM_TILE_NUM_ROWS,
			XAIE_AIE_TILE_ROW_START, XAIE_AIE_TILE_NUM_ROWS);

	XAie_InstDeclare(DevInst, &ConfigPtr);

	RC = XAie_CfgInitialize(&(DevInst), &ConfigPtr);
	CHECK_EQUAL(RC, XAIE_OK);

	auto Aie = std::make_shared<XAieDev>(&DevInst, true);
	auto Stream = Aie->tile(1,2).sswitchPort();

	RC = Stream->getSSIdleEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_ERR);

	RC = Stream->reserve();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSIdleEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSRunningEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSStalledEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSTlastEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, DMA, 0);
	CHECK_EQUAL(RC, XAIE_OK);

	 RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->release();
	CHECK_EQUAL(RC, XAIE_OK);

	/*Test reserve with preferred resource Id*/
	RC = Stream->setPreferredId(1);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->reserve();
	CHECK_EQUAL(RC, XAIE_OK);

	SSRscType = Stream->getRscType();

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, DMA, 0);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->release();
	CHECK_EQUAL(RC, XAIE_OK);

}

TEST(StreamSelect, SSNegativeMemTile) {
	AieRC RC;
	std::vector<XAie_LocType> vL, vL1;
	XAie_Events SSEvent;

	uint32_t SSRscType;

	XAie_ModuleType StartM, EndM, StartM1, EndM1;

	XAie_SetupConfig(ConfigPtr, HW_GEN, XAIE_BASE_ADDR,
			XAIE_COL_SHIFT, XAIE_ROW_SHIFT,
			XAIE_NUM_COLS, XAIE_NUM_ROWS, XAIE_SHIM_ROW,
			XAIE_MEM_TILE_ROW_START, XAIE_MEM_TILE_NUM_ROWS,
			XAIE_AIE_TILE_ROW_START, XAIE_AIE_TILE_NUM_ROWS);

	XAie_InstDeclare(DevInst, &ConfigPtr);

	RC = XAie_CfgInitialize(&(DevInst), &ConfigPtr);
	CHECK_EQUAL(RC, XAIE_OK);

	auto Aie = std::make_shared<XAieDev>(&DevInst, true);
	auto Stream = Aie->tile(1,2).sswitchPort();

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, DMA, 0);
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->getSSIdleEvent(SSEvent);
	CHECK_EQUAL(RC, XAIE_ERR);

	DevInst.IsReady = 0;

	RC = Stream->reserve();
	CHECK_EQUAL(RC, XAIE_INVALID_ARGS);

	DevInst.IsReady = 1;

	RC = Stream->reserve();
	CHECK_EQUAL(RC, XAIE_OK);

	DevInst.IsReady = 0;

	RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_INVALID_ARGS);

	DevInst.IsReady = 1;

	RC = Stream->start();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->setPortToSelect(XAIE_STRMSW_SLAVE, DMA, 0);
	CHECK_EQUAL(RC, XAIE_ERR);

	DevInst.IsReady = 0;

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_INVALID_ARGS);

	DevInst.IsReady = 1;

	RC = Stream->stop();
	CHECK_EQUAL(RC, XAIE_OK);

	RC = Stream->release();
	CHECK_EQUAL(RC, XAIE_OK);

}
#endif
