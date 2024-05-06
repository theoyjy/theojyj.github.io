---

excalidraw-plugin: parsed
tags: [excalidraw]

---
==⚠  Switch to EXCALIDRAW VIEW in the MORE OPTIONS menu of this document. ⚠==


# Text Elements
auto smooth ^Kj7Wz0bX

Linear ^gEKZhDPL

Easy In ^DzSZMewl

Easy Out ^9SUMULt8

每个View的底层数据 ^Ul2Kt984

bSmoothMoveVelocity ^9Ckp6zxT

MoveInTangent ^y3tAuIep

MoveOutTangent ^TQ1k9mz9

true ^Wty9K9Ac

0,0 ^Ef52Uj6b

1, 1 ^QDU7ybSx

false ^ZDE5xs8I

0,0 ^7uWYO4Fv

1, 1 ^XgtgF5LV

true ^T1xcN1I7

x, y ^0jWX8PsL

x, y ^UWUp3IPn

true ^hsrSdWZL

x, y ^c9lyb4Kj

x, y ^II5o48FV

int smooth_move_velocity; ^vtUFPADU

enum MoveVelocity
	{
		None = -1,	// template 和 dcc 轨迹 不展示smooth选项
		Linear = 0,	
		AutoSmooth = 1, // 平滑速度 + 线性时间分布
		UserSmooth = 2  // 平滑曲线 + 用户时间分布
	}; ^QrNTgVhv

MoveInTangent ^OfEzc60g

MoveOutTangent ^3sAbWmdr

-1,-1 ^Q4EQEh6C

0,0 ^gydK7LbJ

1, 1 ^X3MER75S

x, y ^YRidf7kE

x, y ^BUfWLgwf

x, y ^bcLzULxq

x, y ^SmI9xrtA

给前端 ^jdn1AwST

-1,-1 ^NCxMol3U

...... ^XS8yPEk8

FUSION-30558 ^1ElGaepT

view ^VpBPVlzH

InTangent ^hJj18XaF

OutTangent ^LOsCw69H

Time ^GeMBsl6X

0 ^TcNCLBQ1

3 ^mdPtcOID

View ^CW7zgPhs

InTangent ^YHvNJkFC

OutTangent ^OFhQgTOS

Interpolation Of Video Clip:
1. pre View's OutTangent And next View's InTangent form a bezier curve
2. pre View's member bSmooth(Move & Rotate) influent the interval
3. UI adjust for tangents of a single view ^OyV1GDdW

bSmooth ^CmR7frNY

bSmooth ^cdUz3wZQ

Main Process ^L27jjHRB

Load Furniture
Thread ^YqwXNdNY

Spread On Furniture
Thread ^UbJ5B8VP

Actual Load
thread ^iyPLkNhK

mJobs ^MzBKNej5

destroy right away
after create actual 
doing-job thread ^xGCVyfQO

AsyncLoadingModelCVs[stdPath];
AsyncLoadingModelCVMutexs[stdPath];

auto Task = FFunctionGraphTask::CreateAndDispatchWhenReady
(.....);
AsyncLoadingModelTasks.emplace(stdPath, task);
AsyncLoadingModelCVs[stdPath].notify_all(); ^Rm5iJd2D

Actual Spread
Thread ^nM0X1tjQ

If find target Furniture has CV Mutex and CV
    -> wait for Actual Load Task Created: ^8phwuIqX

std::unique_lock<std::mutex> lock(FurnitureCVMutex);
while(!TaskArr.find(FurnitureLoadingPath))
    FurnitureCV.wait();
auto PreTask = TaskArr.find(...) -> second; ^mLtFZtL5

Create Task with PreTask ^lUBB2GIe

FFunctionGraphTask::CreateAndDispatchWhenReady(
    [](){...}, 
    TStatId(), PreTask, 
    ENamedThreads::GameThread);
) ^ROvTOdfc

轨迹 ^oRZ7fqqL

线性运动下：位移在25%，50%，75%的位置 ^tEq1S9L4

线性运动下：旋转在25%，50%，75%的角度 ^Meflpx2B

轨迹 ^QPV1wU6d

自动平滑运动下：时间到25%时，位移可能的位置 ^CUOB1xgb

只改变位移的运动模式
不改变旋转的 ^HKGhhHQG

时间在25%的时候，旋转在线性模式下的旋转没变 ^qMDNPGsn

观测物体 ^faFFkZRs

观测物体 ^874OoTKB

%%
# Drawing
```json
{
	"type": "excalidraw",
	"version": 2,
	"source": "https://github.com/zsviczian/obsidian-excalidraw-plugin/releases/tag/2.0.25",
	"elements": [
		{
			"type": "rectangle",
			"version": 833,
			"versionNonce": 541877707,
			"isDeleted": false,
			"id": "eyJeaGmp6T1UD1wUG-_OT",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3751.5160939354632,
			"y": -1494.5891429128872,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 234.9881756756757,
			"height": 352.34138432384987,
			"seed": 1059774060,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "rectangle",
			"version": 695,
			"versionNonce": 627961957,
			"isDeleted": false,
			"id": "td3HgBA2JoSzs3Q7c7snQ",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3751.0160939354632,
			"y": -1483.34854361794,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 232.49493243243245,
			"height": 46.125,
			"seed": 1593554388,
			"groupIds": [
				"tzQ57BPUTHP0r_IZ2RhsV",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 759,
			"versionNonce": 619934827,
			"isDeleted": false,
			"id": "Kj7Wz0bX",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3726.102242584112,
			"y": -1479.2725301044266,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 186.28172302246094,
			"height": 37.58277027027027,
			"seed": 1130460756,
			"groupIds": [
				"tzQ57BPUTHP0r_IZ2RhsV",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 30.066216216216215,
			"fontFamily": 1,
			"text": "auto smooth",
			"rawText": "auto smooth",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "auto smooth",
			"lineHeight": 1.25,
			"baseline": 26
		},
		{
			"type": "rectangle",
			"version": 716,
			"versionNonce": 1836882885,
			"isDeleted": false,
			"id": "y18NJ10pd6Q1BO6wydXZq",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3753.3944723138416,
			"y": -1430.51186709767,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 232.49493243243245,
			"height": 46.125,
			"seed": 1408685036,
			"groupIds": [
				"f5wRQ_fsFgYN5mPI7be4T",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 826,
			"versionNonce": 721399563,
			"isDeleted": false,
			"id": "gEKZhDPL",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3685.4806209624903,
			"y": -1425.4358535841563,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 88.04570007324219,
			"height": 37.58277027027027,
			"seed": 2085451372,
			"groupIds": [
				"f5wRQ_fsFgYN5mPI7be4T",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 30.066216216216215,
			"fontFamily": 1,
			"text": "Linear",
			"rawText": "Linear",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Linear",
			"lineHeight": 1.25,
			"baseline": 26
		},
		{
			"type": "rectangle",
			"version": 725,
			"versionNonce": 1230953253,
			"isDeleted": false,
			"id": "HWRXI3gN-TflYd35Qpv12",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3752.8944723138416,
			"y": -1371.01186709767,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 232.49493243243245,
			"height": 46.125,
			"seed": 752470636,
			"groupIds": [
				"JJu4dj-Pc6uj--dIliEKh",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 856,
			"versionNonce": 619419051,
			"isDeleted": false,
			"id": "DzSZMewl",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3691.9806209624903,
			"y": -1365.9358535841563,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 116.18185424804688,
			"height": 37.58277027027027,
			"seed": 1519230188,
			"groupIds": [
				"JJu4dj-Pc6uj--dIliEKh",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 30.066216216216215,
			"fontFamily": 1,
			"text": "Easy In",
			"rawText": "Easy In",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Easy In",
			"lineHeight": 1.25,
			"baseline": 26
		},
		{
			"type": "rectangle",
			"version": 712,
			"versionNonce": 562179717,
			"isDeleted": false,
			"id": "trKV8b1nW21fqfjWrsVBS",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3753.3944723138416,
			"y": -1314.01186709767,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 232.49493243243245,
			"height": 46.125,
			"seed": 1183816172,
			"groupIds": [
				"ncW88HqdAyHj9EaimHwBs",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 798,
			"versionNonce": 1373743179,
			"isDeleted": false,
			"id": "9SUMULt8",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3705.9806209624903,
			"y": -1308.9358535841563,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 141.6426544189453,
			"height": 37.58277027027027,
			"seed": 1809677420,
			"groupIds": [
				"ncW88HqdAyHj9EaimHwBs",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 30.066216216216215,
			"fontFamily": 1,
			"text": "Easy Out",
			"rawText": "Easy Out",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Easy Out",
			"lineHeight": 1.25,
			"baseline": 26
		},
		{
			"type": "text",
			"version": 843,
			"versionNonce": 1956910565,
			"isDeleted": false,
			"id": "Ul2Kt984",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2853.8379257604497,
			"y": -1602.7659199185737,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 177.8399658203125,
			"height": 25,
			"seed": 1189774572,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "HcMl8j5Jji9H7FaYEMdeb",
					"type": "arrow"
				},
				{
					"id": "gfL_Aiz9g1Ue1mbeUO8sP",
					"type": "arrow"
				},
				{
					"id": "TE7tssB-aBjHT_1ESWiei",
					"type": "arrow"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "每个View的底层数据",
			"rawText": "每个View的底层数据",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "每个View的底层数据",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 748,
			"versionNonce": 666658539,
			"isDeleted": false,
			"id": "g2PGRg5t1H_LT-gibJlrf",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3073.18976684587,
			"y": -1542.6314687793304,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 209,
			"height": 35,
			"seed": 614855276,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "9Ckp6zxT",
					"type": "text"
				},
				{
					"id": "HcMl8j5Jji9H7FaYEMdeb",
					"type": "arrow"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1380,
			"versionNonce": 231870789,
			"isDeleted": false,
			"id": "9Ckp6zxT",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3068.1096658326865,
			"y": -1537.6314687793304,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 198.8397979736328,
			"height": 25,
			"seed": 2034488532,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "bSmoothMoveVelocity",
			"rawText": "bSmoothMoveVelocity",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "g2PGRg5t1H_LT-gibJlrf",
			"originalText": "bSmoothMoveVelocity",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 747,
			"versionNonce": 2097566091,
			"isDeleted": false,
			"id": "Rn0pUQKLnam6pZJI15FZM",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2832.9160137544395,
			"y": -1541.9077526555611,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 159,
			"height": 35,
			"seed": 939870060,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "y3tAuIep",
					"type": "text"
				},
				{
					"id": "gfL_Aiz9g1Ue1mbeUO8sP",
					"type": "arrow"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1306,
			"versionNonce": 2053742757,
			"isDeleted": false,
			"id": "y3tAuIep",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2827.61595729692,
			"y": -1536.9077526555611,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 148.39988708496094,
			"height": 25,
			"seed": 1802135660,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "MoveInTangent",
			"rawText": "MoveInTangent",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "Rn0pUQKLnam6pZJI15FZM",
			"originalText": "MoveInTangent",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 746,
			"versionNonce": 1928980523,
			"isDeleted": false,
			"id": "zEmGs1kUKdWTmag8pNwqn",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2652.716014873589,
			"y": -1541.3808624277124,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 176,
			"height": 35,
			"seed": 22240364,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "TQ1k9mz9",
					"type": "text"
				},
				{
					"id": "TE7tssB-aBjHT_1ESWiei",
					"type": "arrow"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1330,
			"versionNonce": 1075332101,
			"isDeleted": false,
			"id": "TQ1k9mz9",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2647.3859443779834,
			"y": -1536.3808624277124,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 165.33985900878906,
			"height": 25,
			"seed": 1927694292,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "MoveOutTangent",
			"rawText": "MoveOutTangent",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "zEmGs1kUKdWTmag8pNwqn",
			"originalText": "MoveOutTangent",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 778,
			"versionNonce": 528591563,
			"isDeleted": false,
			"id": "PiV6cBfDt67LVzBivefdu",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3000.8181544689332,
			"y": -1466.6412757835467,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 53,
			"height": 35,
			"seed": 1675637100,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "Wty9K9Ac",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1260,
			"versionNonce": 1390115685,
			"isDeleted": false,
			"id": "Wty9K9Ac",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2995.4181300548707,
			"y": -1461.6412757835467,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 42.199951171875,
			"height": 25,
			"seed": 658397268,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "true",
			"rawText": "true",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "PiV6cBfDt67LVzBivefdu",
			"originalText": "true",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 773,
			"versionNonce": 2000165227,
			"isDeleted": false,
			"id": "oHV91ISWF_C2hms9ahNdQ",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2767.057846491427,
			"y": -1465.9175596597772,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 43,
			"height": 35,
			"seed": 788252268,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "Ef52Uj6b",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1260,
			"versionNonce": 1258342085,
			"isDeleted": false,
			"id": "Ef52Uj6b",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2761.887840693087,
			"y": -1460.9175596597772,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 32.65998840332031,
			"height": 25,
			"seed": 1440106604,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0,0",
			"rawText": "0,0",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "oHV91ISWF_C2hms9ahNdQ",
			"originalText": "0,0",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 770,
			"versionNonce": 2003285003,
			"isDeleted": false,
			"id": "LxkD21pM9Cy7U7S7tb0i9",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2590.4711122917006,
			"y": -1462.2989790409304,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 36,
			"height": 35,
			"seed": 502668140,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "QDU7ybSx",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1264,
			"versionNonce": 1529194021,
			"isDeleted": false,
			"id": "QDU7ybSx",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2585.46111015547,
			"y": -1457.2989790409304,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 25.979995727539062,
			"height": 25,
			"seed": 643303276,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "1, 1",
			"rawText": "1, 1",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "LxkD21pM9Cy7U7S7tb0i9",
			"originalText": "1, 1",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 777,
			"versionNonce": 269154987,
			"isDeleted": false,
			"id": "LN_AGJRxTN6RUX9dNzHoo",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3004.4367350877797,
			"y": -1400.783108520534,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 61,
			"height": 35,
			"seed": 1478439020,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "ZDE5xs8I",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1283,
			"versionNonce": 104307077,
			"isDeleted": false,
			"id": "ZDE5xs8I",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2998.99670975819,
			"y": -1395.783108520534,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 50.11994934082031,
			"height": 25,
			"seed": 1198954196,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "false",
			"rawText": "false",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "LN_AGJRxTN6RUX9dNzHoo",
			"originalText": "false",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 788,
			"versionNonce": 1305242955,
			"isDeleted": false,
			"id": "rVh_9Q8XKIjfp558vA_Jb",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2769.192102498656,
			"y": -1406.4078053447251,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 43,
			"height": 35,
			"seed": 1892091244,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "7uWYO4Fv",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1303,
			"versionNonce": 359932133,
			"isDeleted": false,
			"id": "7uWYO4Fv",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2764.022096700316,
			"y": -1401.4078053447251,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 32.65998840332031,
			"height": 25,
			"seed": 1236102252,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0,0",
			"rawText": "0,0",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "rVh_9Q8XKIjfp558vA_Jb",
			"originalText": "0,0",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 786,
			"versionNonce": 1141279723,
			"isDeleted": false,
			"id": "ecIruBwJPUfhFrBmhu57Y",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2586.8156393087747,
			"y": -1407.1315214684944,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 36,
			"height": 35,
			"seed": 1732090476,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "XgtgF5LV",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1308,
			"versionNonce": 1315486789,
			"isDeleted": false,
			"id": "XgtgF5LV",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2581.8056371725443,
			"y": -1402.1315214684944,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 25.979995727539062,
			"height": 25,
			"seed": 547159788,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "1, 1",
			"rawText": "1, 1",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "ecIruBwJPUfhFrBmhu57Y",
			"originalText": "1, 1",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 800,
			"versionNonce": 918804107,
			"isDeleted": false,
			"id": "IL_ctYgp5Z6rvt_9EuANg",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2999.8829546320826,
			"y": -1345.2537928862134,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 53,
			"height": 35,
			"seed": 664519508,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "T1xcN1I7",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1287,
			"versionNonce": 1760750501,
			"isDeleted": false,
			"id": "T1xcN1I7",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2994.48293021802,
			"y": -1340.2537928862134,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 42.199951171875,
			"height": 25,
			"seed": 2003843284,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "true",
			"rawText": "true",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "IL_ctYgp5Z6rvt_9EuANg",
			"originalText": "true",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 949,
			"versionNonce": 79613227,
			"isDeleted": false,
			"id": "yn1x5NQ4HttBv-juwAuB9",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2787.176427110274,
			"y": -1348.1486573812908,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 1617152364,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "0jWX8PsL",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1460,
			"versionNonce": 1161834245,
			"isDeleted": false,
			"id": "0jWX8PsL",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2755.6933459691763,
			"y": -1342.9200377554134,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 713014252,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "yn1x5NQ4HttBv-juwAuB9",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 953,
			"versionNonce": 1365372875,
			"isDeleted": false,
			"id": "obgdO92Qzt9Ju7SHKMzGR",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2613.8464154675103,
			"y": -1349.1009931309377,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 1837500140,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "UWUp3IPn",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1471,
			"versionNonce": 1640892005,
			"isDeleted": false,
			"id": "UWUp3IPn",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2582.3633343264128,
			"y": -1343.8723735050603,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 595478892,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "obgdO92Qzt9Ju7SHKMzGR",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 817,
			"versionNonce": 1858584171,
			"isDeleted": false,
			"id": "MGXFKwglD3YX_6zIfPL37",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2997.711806260774,
			"y": -1295.3173803461268,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 53,
			"height": 35,
			"seed": 1934623572,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "hsrSdWZL",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1303,
			"versionNonce": 292155845,
			"isDeleted": false,
			"id": "hsrSdWZL",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2992.3117818467117,
			"y": -1290.3173803461268,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 42.199951171875,
			"height": 25,
			"seed": 1117550804,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "true",
			"rawText": "true",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "MGXFKwglD3YX_6zIfPL37",
			"originalText": "true",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 980,
			"versionNonce": 129677579,
			"isDeleted": false,
			"id": "PZ-iCPnzKHkxNv84T8Jbe",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2784.824349708023,
			"y": -1298.326554654143,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 1932132564,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "c9lyb4Kj",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1492,
			"versionNonce": 1899065637,
			"isDeleted": false,
			"id": "c9lyb4Kj",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2753.3412685669255,
			"y": -1293.0979350282655,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 22726228,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "PZ-iCPnzKHkxNv84T8Jbe",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 1006,
			"versionNonce": 162881451,
			"isDeleted": false,
			"id": "ypyHIcjor5NxOajqrZnjF",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2610.7706219414895,
			"y": -1300.0026065275592,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 1750522836,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "II5o48FV",
					"type": "text"
				}
			],
			"updated": 1712906132575,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1518,
			"versionNonce": 512885893,
			"isDeleted": false,
			"id": "II5o48FV",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2579.287540800392,
			"y": -1294.7739869016818,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 305414484,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132575,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "ypyHIcjor5NxOajqrZnjF",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "arrow",
			"version": 2354,
			"versionNonce": 1050349088,
			"isDeleted": false,
			"id": "HcMl8j5Jji9H7FaYEMdeb",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2865.563808559461,
			"y": -1576.0825213097048,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 101.00740277974,
			"height": 22.514104210687037,
			"seed": 1878254572,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125207668,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "Ul2Kt984",
				"gap": 11.846103084664264,
				"focus": 0.25526464544207433
			},
			"endBinding": {
				"elementId": "g2PGRg5t1H_LT-gibJlrf",
				"gap": 10.936948319687417,
				"focus": -0.6855346162287275
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-101.00740277974,
					22.514104210687037
				]
			]
		},
		{
			"type": "arrow",
			"version": 2222,
			"versionNonce": 260441632,
			"isDeleted": false,
			"id": "gfL_Aiz9g1Ue1mbeUO8sP",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2760.3134172513032,
			"y": -1572.3441102126915,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 3.244325561599908,
			"height": 29.436357557129895,
			"seed": 704261076,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125207670,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "Ul2Kt984",
				"gap": 5.421809705882197,
				"focus": -0.02911786026236196
			},
			"endBinding": {
				"elementId": "Rn0pUQKLnam6pZJI15FZM",
				"gap": 1.0000000000002274,
				"focus": -0.01982225987201136
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					3.244325561599908,
					29.436357557129895
				]
			]
		},
		{
			"type": "arrow",
			"version": 2402,
			"versionNonce": 1813184032,
			"isDeleted": false,
			"id": "TE7tssB-aBjHT_1ESWiei",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2668.4869955009917,
			"y": -1575.0698068613233,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.33951918657249,
			"height": 31.7258066145439,
			"seed": 963892076,
			"groupIds": [
				"mMucNkXAMffNuF2YNww_z",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125207670,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "Ul2Kt984",
				"gap": 7.980201277134711,
				"focus": -0.3863837978803792
			},
			"endBinding": {
				"elementId": "zEmGs1kUKdWTmag8pNwqn",
				"gap": 1.9631378190667874,
				"focus": 0.38594071734617547
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					98.33951918657249,
					31.7258066145439
				]
			]
		},
		{
			"type": "text",
			"version": 712,
			"versionNonce": 1566861125,
			"isDeleted": false,
			"id": "vtUFPADU",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "dashed",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3718.0646212578245,
			"y": -1079.4407160653996,
			"strokeColor": "#846358",
			"backgroundColor": "transparent",
			"width": 258.05975341796875,
			"height": 25,
			"seed": 1228217887,
			"groupIds": [
				"EKtyHrWQqKQYoo9i-kiOP",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "int smooth_move_velocity;",
			"rawText": "int smooth_move_velocity;",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "int smooth_move_velocity;",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 751,
			"versionNonce": 1726765963,
			"isDeleted": false,
			"id": "sc2RIMT8RH4fqpu-qmhem",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "dashed",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3716.6646212578244,
			"y": -1030.6282160653998,
			"strokeColor": "#846358",
			"backgroundColor": "transparent",
			"width": 764.8,
			"height": 185,
			"seed": 192238897,
			"groupIds": [
				"EKtyHrWQqKQYoo9i-kiOP",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "QrNTgVhv",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1348,
			"versionNonce": 289486501,
			"isDeleted": false,
			"id": "QrNTgVhv",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "dashed",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3711.6646212578244,
			"y": -1025.6282160653998,
			"strokeColor": "#846358",
			"backgroundColor": "transparent",
			"width": 749.2797241210938,
			"height": 175,
			"seed": 1267110687,
			"groupIds": [
				"EKtyHrWQqKQYoo9i-kiOP",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "enum MoveVelocity\n\t{\n\t\tNone = -1,\t// template 和 dcc 轨迹 不展示smooth选项\n\t\tLinear = 0,\t\n\t\tAutoSmooth = 1, // 平滑速度 + 线性时间分布\n\t\tUserSmooth = 2  // 平滑曲线 + 用户时间分布\n\t};",
			"rawText": "enum MoveVelocity\n\t{\n\t\tNone = -1,\t// template 和 dcc 轨迹 不展示smooth选项\n\t\tLinear = 0,\t\n\t\tAutoSmooth = 1, // 平滑速度 + 线性时间分布\n\t\tUserSmooth = 2  // 平滑曲线 + 用户时间分布\n\t};",
			"textAlign": "left",
			"verticalAlign": "middle",
			"containerId": "sc2RIMT8RH4fqpu-qmhem",
			"originalText": "enum MoveVelocity\n\t{\n\t\tNone = -1,\t// template 和 dcc 轨迹 不展示smooth选项\n\t\tLinear = 0,\t\n\t\tAutoSmooth = 1, // 平滑速度 + 线性时间分布\n\t\tUserSmooth = 2  // 平滑曲线 + 用户时间分布\n\t};",
			"lineHeight": 1.25,
			"baseline": 166
		},
		{
			"type": "rectangle",
			"version": 664,
			"versionNonce": 126792235,
			"isDeleted": false,
			"id": "NoqMgCUPeunS8r29ERbQv",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3494.918170814073,
			"y": -1544.330185070378,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 159,
			"height": 35,
			"seed": 524356703,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "OfEzc60g",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1224,
			"versionNonce": 59578885,
			"isDeleted": false,
			"id": "OfEzc60g",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3489.6181143565536,
			"y": -1539.330185070378,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 148.39988708496094,
			"height": 25,
			"seed": 893266047,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "MoveInTangent",
			"rawText": "MoveInTangent",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "NoqMgCUPeunS8r29ERbQv",
			"originalText": "MoveInTangent",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 665,
			"versionNonce": 451753163,
			"isDeleted": false,
			"id": "FQ84t_9wWaQMspIqCvKgH",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3314.7181719332225,
			"y": -1543.8032948425296,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 176,
			"height": 35,
			"seed": 562217119,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "3sAbWmdr",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1248,
			"versionNonce": 1027969381,
			"isDeleted": false,
			"id": "3sAbWmdr",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3309.388101437617,
			"y": -1538.8032948425296,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 165.33985900878906,
			"height": 25,
			"seed": 633296063,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "MoveOutTangent",
			"rawText": "MoveOutTangent",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "FQ84t_9wWaQMspIqCvKgH",
			"originalText": "MoveOutTangent",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 708,
			"versionNonce": 1352819563,
			"isDeleted": false,
			"id": "gobnv_8AIhw0TPYxRGtaL",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3429.0600035510606,
			"y": -1468.3399920745944,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 43,
			"height": 35,
			"seed": 2039768287,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "Q4EQEh6C",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1185,
			"versionNonce": 1270357189,
			"isDeleted": false,
			"id": "Q4EQEh6C",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3423.769987376744,
			"y": -1463.3399920745944,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 32.41996765136719,
			"height": 25,
			"seed": 210923775,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "-1,-1",
			"rawText": "-1,-1",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "gobnv_8AIhw0TPYxRGtaL",
			"originalText": "-1,-1",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 704,
			"versionNonce": 16301579,
			"isDeleted": false,
			"id": "vLJzK5WI3UuPu7kPPZUoA",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3431.1942595582896,
			"y": -1408.8302377595421,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 43,
			"height": 35,
			"seed": 1295482207,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "gydK7LbJ",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1219,
			"versionNonce": 914504741,
			"isDeleted": false,
			"id": "gydK7LbJ",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3426.0242537599497,
			"y": -1403.8302377595421,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 32.65998840332031,
			"height": 25,
			"seed": 490633599,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0,0",
			"rawText": "0,0",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "vLJzK5WI3UuPu7kPPZUoA",
			"originalText": "0,0",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 706,
			"versionNonce": 384484523,
			"isDeleted": false,
			"id": "3E-g8tkypp-iTskkdYOH7",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3248.8177963684084,
			"y": -1409.5539538833116,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 36,
			"height": 35,
			"seed": 659616159,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "X3MER75S",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1225,
			"versionNonce": 898723717,
			"isDeleted": false,
			"id": "X3MER75S",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3243.807794232178,
			"y": -1404.5539538833116,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 25.979995727539062,
			"height": 25,
			"seed": 345990591,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "1, 1",
			"rawText": "1, 1",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "3E-g8tkypp-iTskkdYOH7",
			"originalText": "1, 1",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 868,
			"versionNonce": 975370059,
			"isDeleted": false,
			"id": "8Ct16djmj0hxOmo8QjxHX",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3449.1785841699075,
			"y": -1350.5710897961076,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 340415967,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "YRidf7kE",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1380,
			"versionNonce": 656619237,
			"isDeleted": false,
			"id": "YRidf7kE",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3417.69550302881,
			"y": -1345.3424701702302,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 492978687,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "8Ct16djmj0hxOmo8QjxHX",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 872,
			"versionNonce": 956028395,
			"isDeleted": false,
			"id": "xa7SbIdduTfC9JswXq3q5",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3275.848572527144,
			"y": -1351.5234255457544,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 1894230559,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "BUfWLgwf",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1389,
			"versionNonce": 1170543173,
			"isDeleted": false,
			"id": "BUfWLgwf",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3244.3654913860464,
			"y": -1346.294805919877,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 1540034111,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "xa7SbIdduTfC9JswXq3q5",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 896,
			"versionNonce": 847241355,
			"isDeleted": false,
			"id": "MDN2vwx7JWBy4J4rT3cId",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3446.8265067676566,
			"y": -1300.74898706896,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 955051615,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "bcLzULxq",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1410,
			"versionNonce": 508854693,
			"isDeleted": false,
			"id": "bcLzULxq",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3415.343425626559,
			"y": -1295.5203674430827,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 857590399,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "MDN2vwx7JWBy4J4rT3cId",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 923,
			"versionNonce": 6919979,
			"isDeleted": false,
			"id": "0AEVowbvH1mlJwAaVmOKY",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3272.772779001123,
			"y": -1302.4250389423764,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.72614153024142,
			"height": 35.45723925175497,
			"seed": 1193157279,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "SmI9xrtA",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1437,
			"versionNonce": 1174340869,
			"isDeleted": false,
			"id": "SmI9xrtA",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3241.2896978600256,
			"y": -1297.196419316499,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 35.759979248046875,
			"height": 25,
			"seed": 94271167,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "x, y",
			"rawText": "x, y",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "0AEVowbvH1mlJwAaVmOKY",
			"originalText": "x, y",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "text",
			"version": 660,
			"versionNonce": 1629714891,
			"isDeleted": false,
			"id": "jdn1AwST",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3339.5557385051507,
			"y": -1595.8509053127177,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 60,
			"height": 25,
			"seed": 361606257,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "给前端",
			"rawText": "给前端",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "给前端",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "rectangle",
			"version": 731,
			"versionNonce": 1346509925,
			"isDeleted": false,
			"id": "FXKCgmAvpGKFbKcPwdlfb",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3253.1030020688004,
			"y": -1470.3578172220564,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 43,
			"height": 35,
			"seed": 654340799,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "NCxMol3U",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1204,
			"versionNonce": 1640499307,
			"isDeleted": false,
			"id": "NCxMol3U",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3247.812985894484,
			"y": -1465.3578172220564,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 32.41996765136719,
			"height": 25,
			"seed": 822199007,
			"groupIds": [
				"7qnlGmkAhQUpHXbOh_m1p",
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "-1,-1",
			"rawText": "-1,-1",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "FXKCgmAvpGKFbKcPwdlfb",
			"originalText": "-1,-1",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "text",
			"version": 511,
			"versionNonce": 82528197,
			"isDeleted": false,
			"id": "XS8yPEk8",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3650.4041482104885,
			"y": -1241.819723732537,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 32.879974365234375,
			"height": 25,
			"seed": 187097681,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "......",
			"rawText": "......",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "......",
			"lineHeight": 1.25,
			"baseline": 16
		},
		{
			"type": "arrow",
			"version": 781,
			"versionNonce": 136430347,
			"isDeleted": false,
			"id": "v51KSpL5ipXXGifzu7enp",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3184.5289278042414,
			"y": -1455.011212728829,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 166.31578947368428,
			"height": 1.0526315789473983,
			"seed": 771416977,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					166.31578947368428,
					-1.0526315789473983
				]
			]
		},
		{
			"type": "arrow",
			"version": 853,
			"versionNonce": 1444415269,
			"isDeleted": false,
			"id": "ALd-9hSyXys2ZpDM-lLEq",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3187.0351595009097,
			"y": -1387.4731408076943,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 166.31578947368428,
			"height": 1.0526315789473983,
			"seed": 230792593,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					166.31578947368428,
					-1.0526315789473983
				]
			]
		},
		{
			"type": "arrow",
			"version": 928,
			"versionNonce": 1017850283,
			"isDeleted": false,
			"id": "QD0joK_t7RXZnYm0f2Dqr",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3022.673689403183,
			"y": -1444.3571317782616,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 163.15789473684197,
			"height": 3.1578947368420813,
			"seed": 959600319,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-163.15789473684197,
					3.1578947368420813
				]
			]
		},
		{
			"type": "arrow",
			"version": 969,
			"versionNonce": 372628101,
			"isDeleted": false,
			"id": "tO1SJ8AeM-vtaB-ruwk03",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3022.627765189523,
			"y": -1377.1383046020132,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 168.42105263157885,
			"height": 1.0526315789473983,
			"seed": 1327602001,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-168.42105263157885,
					1.0526315789473983
				]
			]
		},
		{
			"type": "line",
			"version": 521,
			"versionNonce": 1955511371,
			"isDeleted": false,
			"id": "bnRwy4RAKLOFlTfSRsG3G",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "dashed",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3107.6868225410835,
			"y": -1672.9059495709341,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 5.263157894736878,
			"height": 564.2105263157894,
			"seed": 1846601361,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					5.263157894736878,
					564.2105263157894
				]
			]
		},
		{
			"type": "text",
			"version": 656,
			"versionNonce": 1845641701,
			"isDeleted": false,
			"id": "1ElGaepT",
			"fillStyle": "solid",
			"strokeWidth": 2,
			"strokeStyle": "dashed",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3736.928406248961,
			"y": -1671.5975522841188,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 273.3118896484375,
			"height": 45,
			"seed": 819084081,
			"groupIds": [
				"zCUNFeS8omi_K6eOOs4Rf"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "FUSION-30558",
			"rawText": "FUSION-30558",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "FUSION-30558",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "rectangle",
			"version": 249,
			"versionNonce": 463928043,
			"isDeleted": false,
			"id": "QoYP1Z18yAx8ojakaqC7l",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3710.3231770491516,
			"y": -244.2793087440807,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 186.66666666666652,
			"height": 112.22222222222229,
			"seed": 581890874,
			"groupIds": [
				"g1HlteQ7oKRivbx3H9Uba",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "MgG0m5M4wqn9v0cSxVd4b",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 245,
			"versionNonce": 311082309,
			"isDeleted": false,
			"id": "VpBPVlzH",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3652.5453992713733,
			"y": -215.39041985519168,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 68.32795715332031,
			"height": 45,
			"seed": 262702630,
			"groupIds": [
				"g1HlteQ7oKRivbx3H9Uba",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "view",
			"rawText": "view",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "view",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "arrow",
			"version": 1126,
			"versionNonce": 1048470923,
			"isDeleted": false,
			"id": "MgG0m5M4wqn9v0cSxVd4b",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3806.9001115628,
			"y": -270.5733227424304,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 164.26627333527813,
			"height": 0.2304552007270786,
			"seed": 2134663846,
			"groupIds": [
				"MTCqyB7r41fsoFuuBtzm5",
				"g1HlteQ7oKRivbx3H9Uba",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": {
				"elementId": "QoYP1Z18yAx8ojakaqC7l",
				"focus": 1.4604497926361648,
				"gap": 26.06355879762259
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					164.26627333527813,
					0.2304552007270786
				]
			]
		},
		{
			"type": "text",
			"version": 508,
			"versionNonce": 992791717,
			"isDeleted": false,
			"id": "hJj18XaF",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3819.4990759222146,
			"y": -340.439716610878,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 181.0799560546875,
			"height": 45,
			"seed": 618372090,
			"groupIds": [
				"MTCqyB7r41fsoFuuBtzm5",
				"g1HlteQ7oKRivbx3H9Uba",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "InTangent",
			"rawText": "InTangent",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "InTangent",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "arrow",
			"version": 1447,
			"versionNonce": 1951366187,
			"isDeleted": false,
			"id": "moo7t4JlYQalNHHe14-B7",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3595.096178113449,
			"y": -272.9143689640813,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 164.26627333525266,
			"height": 0.2304552007270786,
			"seed": 1489954298,
			"groupIds": [
				"zfORRFnhTeQUmKxUz7JIl",
				"g1HlteQ7oKRivbx3H9Uba",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					164.26627333525266,
					0.2304552007270786
				]
			]
		},
		{
			"type": "text",
			"version": 546,
			"versionNonce": 1469444101,
			"isDeleted": false,
			"id": "LOsCw69H",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3607.6951424728636,
			"y": -342.7807628325289,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 211.5719451904297,
			"height": 45,
			"seed": 682890938,
			"groupIds": [
				"zfORRFnhTeQUmKxUz7JIl",
				"g1HlteQ7oKRivbx3H9Uba",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "nQ5sBSo0qCWc9A0ExLOvU",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "OutTangent",
			"rawText": "OutTangent",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "OutTangent",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "arrow",
			"version": 224,
			"versionNonce": 151305931,
			"isDeleted": false,
			"id": "m_KlOHyln3WEGltNDrNLA",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3797.1551644455203,
			"y": -83.0148205519796,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 1445.7142857142858,
			"height": 1.4285714285714448,
			"seed": 1915497466,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": {
				"elementId": "GeMBsl6X",
				"focus": -0.7787904064990113,
				"gap": 14.28571428571422
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					1445.7142857142858,
					1.4285714285714448
				]
			]
		},
		{
			"type": "text",
			"version": 89,
			"versionNonce": 96708453,
			"isDeleted": false,
			"id": "GeMBsl6X",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2337.1551644455203,
			"y": -121.58624912340815,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 79.30796813964844,
			"height": 45,
			"seed": 1758740154,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "m_KlOHyln3WEGltNDrNLA",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Time",
			"rawText": "Time",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Time",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "text",
			"version": 109,
			"versionNonce": 1731767659,
			"isDeleted": false,
			"id": "TcNCLBQ1",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3632.8694501598065,
			"y": -61.824344361503336,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 24.767990112304688,
			"height": 45,
			"seed": 928673574,
			"groupIds": [
				"3wfbtPIyaYeddYVe7CCVV",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "0",
			"rawText": "0",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "0",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "line",
			"version": 211,
			"versionNonce": 1208185541,
			"isDeleted": false,
			"id": "_6gelNlr0S1elSipA3j_7",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3621.440878731235,
			"y": -373.2529157900748,
			"strokeColor": "#2f9e44",
			"backgroundColor": "transparent",
			"width": 0,
			"height": 385.71428571428567,
			"seed": 718378426,
			"groupIds": [
				"3wfbtPIyaYeddYVe7CCVV",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					0,
					385.71428571428567
				]
			]
		},
		{
			"type": "rectangle",
			"version": 316,
			"versionNonce": 1110820875,
			"isDeleted": false,
			"id": "A6zuhf59cRrShj6f3gKJf",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3116.0374627634374,
			"y": -249.4380389028106,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 186.66666666666652,
			"height": 112.22222222222229,
			"seed": 818176550,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"type": "text",
					"id": "CW7zgPhs"
				},
				{
					"id": "cZDU5An6jGS-sJtWEAq_G",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 184,
			"versionNonce": 2062733861,
			"isDeleted": false,
			"id": "CW7zgPhs",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3056.7601139271746,
			"y": -215.82692779169946,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 68.11196899414062,
			"height": 45,
			"seed": 645611962,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "View",
			"rawText": "View",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "A6zuhf59cRrShj6f3gKJf",
			"originalText": "View",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "arrow",
			"version": 1142,
			"versionNonce": 156121632,
			"isDeleted": false,
			"id": "cZDU5An6jGS-sJtWEAq_G",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3211.9584251202828,
			"y": -267.4581315675414,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 164.26627333524948,
			"height": 0.2304552007270786,
			"seed": 209333542,
			"groupIds": [
				"pnD_5yXMj1dA5DkvIb0lU",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125207672,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": {
				"elementId": "A6zuhf59cRrShj6f3gKJf",
				"gap": 17.789637464003704,
				"focus": 1.3133534337791504
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					164.26627333524948,
					0.2304552007270786
				]
			]
		},
		{
			"type": "text",
			"version": 541,
			"versionNonce": 192890245,
			"isDeleted": false,
			"id": "YHvNJkFC",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3224.5573894796976,
			"y": -337.324525435989,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 181.0799560546875,
			"height": 45,
			"seed": 1413847142,
			"groupIds": [
				"pnD_5yXMj1dA5DkvIb0lU",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "-AHZhtBtRGH-XmRRJtonE",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "InTangent",
			"rawText": "InTangent",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "InTangent",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "arrow",
			"version": 1438,
			"versionNonce": 1663402315,
			"isDeleted": false,
			"id": "dkf31JbGkMCzZTDxJ8gQd",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -2895.746409573996,
			"y": -269.65269984805036,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 59.85819123831743,
			"height": 0.08397725958536739,
			"seed": 1040292774,
			"groupIds": [
				"8QHkVklqsXvw7TPdJrzqV",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					59.85819123831743,
					0.08397725958536739
				]
			]
		},
		{
			"type": "text",
			"version": 575,
			"versionNonce": 1827032293,
			"isDeleted": false,
			"id": "OFhQgTOS",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3012.753456030346,
			"y": -339.6655716576397,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 211.5719451904297,
			"height": 45,
			"seed": 1876637414,
			"groupIds": [
				"8QHkVklqsXvw7TPdJrzqV",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "OutTangent",
			"rawText": "OutTangent",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "OutTangent",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "text",
			"version": 84,
			"versionNonce": 1964842987,
			"isDeleted": false,
			"id": "mdPtcOID",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -3047.1551644455208,
			"y": -58.729106266265376,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 24.5159912109375,
			"height": 45,
			"seed": 1971154618,
			"groupIds": [
				"EIqRS1NM5hSrZcfuIe88H",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "3",
			"rawText": "3",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "3",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "line",
			"version": 204,
			"versionNonce": 1320511557,
			"isDeleted": false,
			"id": "42-htjCzX_vQfEfYWUI7F",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3032.253103236679,
			"y": -361.26919285548695,
			"strokeColor": "#2f9e44",
			"backgroundColor": "transparent",
			"width": 0,
			"height": 385.71428571428567,
			"seed": 630751802,
			"groupIds": [
				"EIqRS1NM5hSrZcfuIe88H",
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					0,
					385.71428571428567
				]
			]
		},
		{
			"type": "rectangle",
			"version": 140,
			"versionNonce": 803728011,
			"isDeleted": false,
			"id": "MuFbSyoM9TJZlxGBjnSxD",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3454.298021588378,
			"y": -25.871963409122372,
			"strokeColor": "#1971c2",
			"backgroundColor": "#b2f2bb",
			"width": 247.14285714285734,
			"height": 215.71428571428567,
			"seed": 1645440122,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "jl73obvNJ3ka3JduTnORY",
					"type": "arrow"
				},
				{
					"id": "ytKXm-0koPB2fUYTSwPT3",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "freedraw",
			"version": 153,
			"versionNonce": 315234213,
			"isDeleted": false,
			"id": "mAuQBQCJEnfAL9CyBmc4l",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3450.0123073026634,
			"y": 172.69946516230607,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "#b2f2bb",
			"width": 231.4285714285711,
			"height": 198.57142857142856,
			"seed": 1146957370,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					1.4285714285711038,
					0
				],
				[
					2.8571428571426623,
					0
				],
				[
					4.285714285713766,
					0
				],
				[
					5.7142857142853245,
					0
				],
				[
					8.571428571428442,
					0
				],
				[
					10,
					0
				],
				[
					12.857142857142662,
					0
				],
				[
					14.285714285713766,
					0
				],
				[
					15.714285714285325,
					-1.4285714285714448
				],
				[
					20,
					-1.4285714285714448
				],
				[
					22.857142857142662,
					-1.4285714285714448
				],
				[
					25.714285714285325,
					-1.4285714285714448
				],
				[
					27.142857142856883,
					-1.4285714285714448
				],
				[
					30,
					-1.4285714285714448
				],
				[
					31.428571428571104,
					-1.4285714285714448
				],
				[
					34.285714285713766,
					-2.857142857142776
				],
				[
					37.14285714285688,
					-2.857142857142776
				],
				[
					40,
					-4.285714285714221
				],
				[
					42.85714285714266,
					-5.714285714285666
				],
				[
					48.57142857142844,
					-5.714285714285666
				],
				[
					52.85714285714266,
					-7.14285714285711
				],
				[
					57.14285714285688,
					-8.571428571428555
				],
				[
					62.85714285714266,
					-11.428571428571445
				],
				[
					68.57142857142844,
					-14.28571428571422
				],
				[
					74.28571428571377,
					-17.14285714285711
				],
				[
					77.14285714285688,
					-20
				],
				[
					82.85714285714266,
					-21.428571428571445
				],
				[
					85.71428571428532,
					-22.857142857142776
				],
				[
					90,
					-24.28571428571422
				],
				[
					94.28571428571377,
					-27.14285714285711
				],
				[
					100,
					-31.428571428571445
				],
				[
					105.71428571428532,
					-34.28571428571422
				],
				[
					111.4285714285711,
					-38.571428571428555
				],
				[
					118.57142857142844,
					-42.857142857142776
				],
				[
					122.85714285714266,
					-47.14285714285711
				],
				[
					128.57142857142844,
					-51.428571428571445
				],
				[
					132.85714285714266,
					-54.28571428571422
				],
				[
					137.14285714285688,
					-60
				],
				[
					142.85714285714266,
					-64.28571428571422
				],
				[
					147.14285714285688,
					-70
				],
				[
					150,
					-74.28571428571422
				],
				[
					154.28571428571377,
					-80
				],
				[
					157.14285714285688,
					-82.85714285714278
				],
				[
					161.4285714285711,
					-88.57142857142856
				],
				[
					164.28571428571377,
					-94.28571428571422
				],
				[
					170,
					-98.57142857142856
				],
				[
					172.85714285714266,
					-107.14285714285711
				],
				[
					178.57142857142844,
					-112.85714285714278
				],
				[
					182.85714285714266,
					-120
				],
				[
					187.14285714285688,
					-125.71428571428567
				],
				[
					188.57142857142844,
					-127.14285714285711
				],
				[
					190,
					-128.57142857142856
				],
				[
					191.4285714285711,
					-131.42857142857144
				],
				[
					194.28571428571377,
					-137.1428571428571
				],
				[
					197.14285714285688,
					-140
				],
				[
					198.57142857142844,
					-142.85714285714278
				],
				[
					200,
					-144.28571428571422
				],
				[
					201.4285714285711,
					-148.57142857142856
				],
				[
					202.85714285714266,
					-151.42857142857133
				],
				[
					205.71428571428532,
					-155.71428571428567
				],
				[
					207.14285714285688,
					-160
				],
				[
					208.57142857142844,
					-162.85714285714278
				],
				[
					211.4285714285711,
					-167.1428571428571
				],
				[
					214.28571428571377,
					-170
				],
				[
					215.71428571428532,
					-172.85714285714278
				],
				[
					217.14285714285688,
					-177.1428571428571
				],
				[
					217.14285714285688,
					-180
				],
				[
					220,
					-182.85714285714278
				],
				[
					222.85714285714266,
					-184.28571428571422
				],
				[
					225.71428571428532,
					-187.1428571428571
				],
				[
					225.71428571428532,
					-190
				],
				[
					227.14285714285688,
					-191.42857142857133
				],
				[
					228.57142857142844,
					-192.85714285714278
				],
				[
					230,
					-194.28571428571422
				],
				[
					230,
					-195.71428571428567
				],
				[
					231.4285714285711,
					-198.57142857142856
				],
				[
					231.4285714285711,
					-198.57142857142856
				]
			],
			"lastCommittedPoint": null,
			"simulatePressure": true,
			"pressures": []
		},
		{
			"type": "arrow",
			"version": 106,
			"versionNonce": 1749049643,
			"isDeleted": false,
			"id": "YvrQU65FuoIsE5aX2D-4_",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3450.0123073026634,
			"y": 172.69946516230607,
			"strokeColor": "#e03131",
			"backgroundColor": "#b2f2bb",
			"width": 160,
			"height": 4.285714285714334,
			"seed": 740928058,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					160,
					4.285714285714334
				]
			]
		},
		{
			"type": "arrow",
			"version": 162,
			"versionNonce": 55696133,
			"isDeleted": false,
			"id": "jl73obvNJ3ka3JduTnORY",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3220.0123073026634,
			"y": -27.30053483769393,
			"strokeColor": "#e03131",
			"backgroundColor": "#b2f2bb",
			"width": 25.714285714286234,
			"height": 140,
			"seed": 678627494,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "MuFbSyoM9TJZlxGBjnSxD",
				"focus": -0.6321675477836503,
				"gap": 1.4285714285715585
			},
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-25.714285714286234,
					140
				]
			]
		},
		{
			"type": "arrow",
			"version": 271,
			"versionNonce": 2005992395,
			"isDeleted": false,
			"id": "nQ5sBSo0qCWc9A0ExLOvU",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3495.7265930169497,
			"y": -288.72910626626526,
			"strokeColor": "#f08c00",
			"backgroundColor": "#b2f2bb",
			"width": 162.85714285714312,
			"height": 437.1428571428571,
			"seed": 1075763366,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "LOsCw69H",
				"focus": 0.04880479619795896,
				"gap": 9.05165656626366
			},
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					162.85714285714312,
					437.1428571428571
				]
			]
		},
		{
			"type": "arrow",
			"version": 191,
			"versionNonce": 1221210725,
			"isDeleted": false,
			"id": "-AHZhtBtRGH-XmRRJtonE",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "dashed",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3172.8694501598065,
			"y": -290.1576776948367,
			"strokeColor": "#f08c00",
			"backgroundColor": "#b2f2bb",
			"width": 44.28571428571422,
			"height": 331.42857142857133,
			"seed": 1193719738,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "YHvNJkFC",
				"focus": 0.3800896768856261,
				"gap": 2.16684774115231
			},
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-44.28571428571422,
					331.42857142857133
				]
			]
		},
		{
			"type": "text",
			"version": 407,
			"versionNonce": 636768875,
			"isDeleted": false,
			"id": "OyV1GDdW",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3852.9884977788556,
			"y": -576.2291062662654,
			"strokeColor": "#099268",
			"backgroundColor": "#b2f2bb",
			"width": 1289.51953125,
			"height": 180,
			"seed": 1777541562,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Interpolation Of Video Clip:\n1. pre View's OutTangent And next View's InTangent form a bezier curve\n2. pre View's member bSmooth(Move & Rotate) influent the interval\n3. UI adjust for tangents of a single view",
			"rawText": "Interpolation Of Video Clip:\n1. pre View's OutTangent And next View's InTangent form a bezier curve\n2. pre View's member bSmooth(Move & Rotate) influent the interval\n3. UI adjust for tangents of a single view",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Interpolation Of Video Clip:\n1. pre View's OutTangent And next View's InTangent form a bezier curve\n2. pre View's member bSmooth(Move & Rotate) influent the interval\n3. UI adjust for tangents of a single view",
			"lineHeight": 1.25,
			"baseline": 167
		},
		{
			"type": "text",
			"version": 149,
			"versionNonce": 536911301,
			"isDeleted": false,
			"id": "CmR7frNY",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3691.321831112189,
			"y": -181.22910626626492,
			"strokeColor": "#f08c00",
			"backgroundColor": "#b2f2bb",
			"width": 140.97598266601562,
			"height": 45,
			"seed": 1068551802,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "ytKXm-0koPB2fUYTSwPT3",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "bSmooth",
			"rawText": "bSmooth",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "bSmooth",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "text",
			"version": 177,
			"versionNonce": 1412746507,
			"isDeleted": false,
			"id": "cdUz3wZQ",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3096.8098224451965,
			"y": -185.39577293293166,
			"strokeColor": "#f08c00",
			"backgroundColor": "#b2f2bb",
			"width": 140.97598266601562,
			"height": 45,
			"seed": 1689527162,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "bSmooth",
			"rawText": "bSmooth",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "bSmooth",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "arrow",
			"version": 291,
			"versionNonce": 1343397157,
			"isDeleted": false,
			"id": "ytKXm-0koPB2fUYTSwPT3",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3601.3218311121886,
			"y": -127.89577293293189,
			"strokeColor": "#f08c00",
			"backgroundColor": "#b2f2bb",
			"width": 141.66666666666652,
			"height": 228.33333333333337,
			"seed": 580142630,
			"groupIds": [
				"p_LR_gv1VFa467gywqvEA"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "CmR7frNY",
				"focus": -0.004521587840630143,
				"gap": 8.33333333333303
			},
			"endBinding": {
				"elementId": "MuFbSyoM9TJZlxGBjnSxD",
				"focus": -0.736926136778343,
				"gap": 5.357142857143799
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					141.66666666666652,
					228.33333333333337
				]
			]
		},
		{
			"type": "rectangle",
			"version": 112,
			"versionNonce": 1707930539,
			"isDeleted": false,
			"id": "DCiFZb773yC2KIKup2J8w",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -4031.042847042364,
			"y": 909.6753352504202,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 412,
			"height": 234,
			"seed": 1207038034,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 97,
			"versionNonce": 1617801349,
			"isDeleted": false,
			"id": "L27jjHRB",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3940.820624820142,
			"y": 1003.6753352504202,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 230.36390686035156,
			"height": 45,
			"seed": 1278183950,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Main Process",
			"rawText": "Main Process",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Main Process",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "arrow",
			"version": 74,
			"versionNonce": 1793541707,
			"isDeleted": false,
			"id": "b_gIKzDVD6DzdM7Vb8e70",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3621.042847042364,
			"y": 1009.6753352504202,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 314,
			"height": 201.4124263257744,
			"seed": 1203012370,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": {
				"elementId": "BDRLJsOz9k0kipzPnV0W9",
				"focus": 0.6021495659298634,
				"gap": 4.66666666666697
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					314,
					-201.4124263257744
				]
			]
		},
		{
			"type": "arrow",
			"version": 95,
			"versionNonce": 248469477,
			"isDeleted": false,
			"id": "T5VgpcMdOLLog5sjs3ZWn",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3623.042847042364,
			"y": 1015.6753352504202,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 316.181818181818,
			"height": 191.75459633568198,
			"seed": 1653143442,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": {
				"elementId": "hSVKxJTpLS0bo-dIni2qm",
				"focus": -0.5812489647175745,
				"gap": 1
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					316.181818181818,
					191.75459633568198
				]
			]
		},
		{
			"type": "rectangle",
			"version": 379,
			"versionNonce": 173950187,
			"isDeleted": false,
			"id": "ZR0Im0-qxo6dGJtnZ4cy6",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -1132.6792106787273,
			"y": 739.6924292675142,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 448,
			"height": 218,
			"seed": 1095964110,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"type": "text",
					"id": "iyPLkNhK"
				},
				{
					"id": "TcoMEUefV95TTONa8DwhK",
					"type": "arrow"
				},
				{
					"id": "Nq-LPcndKHF8qfEFoPTGp",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 337,
			"versionNonce": 88412997,
			"isDeleted": false,
			"id": "iyPLkNhK",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -1018.6591835180827,
			"y": 803.6924292675142,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 219.95994567871094,
			"height": 90,
			"seed": 1659522258,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Actual Load\nthread",
			"rawText": "Actual Load\nthread",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "ZR0Im0-qxo6dGJtnZ4cy6",
			"originalText": "Actual Load\nthread",
			"lineHeight": 1.25,
			"baseline": 77
		},
		{
			"type": "arrow",
			"version": 638,
			"versionNonce": 733769611,
			"isDeleted": false,
			"id": "TcoMEUefV95TTONa8DwhK",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2866.376180375697,
			"y": 843.6032077597059,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 221.70085470085405,
			"height": 3.1648403955929325,
			"seed": 613895314,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "BDRLJsOz9k0kipzPnV0W9",
				"focus": 0.36950267973286904,
				"gap": 6
			},
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					221.70085470085405,
					-3.1648403955929325
				]
			]
		},
		{
			"type": "rectangle",
			"version": 120,
			"versionNonce": 1345086117,
			"isDeleted": false,
			"id": "BDRLJsOz9k0kipzPnV0W9",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3302.376180375697,
			"y": 711.4127089877941,
			"strokeColor": "#2f9e44",
			"backgroundColor": "transparent",
			"width": 430,
			"height": 196,
			"seed": 234385294,
			"groupIds": [
				"hnbeKiVs-lqC_EII_j17j"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "TcoMEUefV95TTONa8DwhK",
					"type": "arrow"
				},
				{
					"id": "b_gIKzDVD6DzdM7Vb8e70",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 147,
			"versionNonce": 1631340075,
			"isDeleted": false,
			"id": "YqwXNdNY",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3225.042847042364,
			"y": 781.6753352504202,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 261.2519226074219,
			"height": 90,
			"seed": 288981134,
			"groupIds": [
				"hnbeKiVs-lqC_EII_j17j"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Load Furniture\nThread",
			"rawText": "Load Furniture\nThread",
			"textAlign": "center",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Load Furniture\nThread",
			"lineHeight": 1.25,
			"baseline": 77
		},
		{
			"type": "rectangle",
			"version": 135,
			"versionNonce": 338871813,
			"isDeleted": false,
			"id": "hSVKxJTpLS0bo-dIni2qm",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3305.861028860546,
			"y": 1107.6753352504202,
			"strokeColor": "#2f9e44",
			"backgroundColor": "transparent",
			"width": 430,
			"height": 196,
			"seed": 1681549966,
			"groupIds": [
				"hnbeKiVs-lqC_EII_j17j"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "T5VgpcMdOLLog5sjs3ZWn",
					"type": "arrow"
				},
				{
					"id": "b9ByDjKLWJ0B_jsXnizT5",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 209,
			"versionNonce": 298338507,
			"isDeleted": false,
			"id": "UbJ5B8VP",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3267.166824703497,
			"y": 1171.6753352504202,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 355.4998779296875,
			"height": 90,
			"seed": 250210510,
			"groupIds": [
				"hnbeKiVs-lqC_EII_j17j"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Spread On Furniture\nThread",
			"rawText": "Spread On Furniture\nThread",
			"textAlign": "center",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Spread On Furniture\nThread",
			"lineHeight": 1.25,
			"baseline": 77
		},
		{
			"type": "rectangle",
			"version": 181,
			"versionNonce": 72727909,
			"isDeleted": false,
			"id": "jUXpELQyaNRBfp9Nrg1Rc",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dashed",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3387.265069264586,
			"y": 518.7864463615314,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 573.333333333333,
			"height": 1602.2222222222222,
			"seed": 135321102,
			"groupIds": [
				"hnbeKiVs-lqC_EII_j17j"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 64,
			"versionNonce": 1660614507,
			"isDeleted": false,
			"id": "MzBKNej5",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3170.072164262416,
			"y": 536.5642241393091,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 103.3919677734375,
			"height": 45,
			"seed": 229814482,
			"groupIds": [
				"hnbeKiVs-lqC_EII_j17j"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "mJobs",
			"rawText": "mJobs",
			"textAlign": "center",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "mJobs",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "text",
			"version": 313,
			"versionNonce": 400738501,
			"isDeleted": false,
			"id": "xGCVyfQO",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3288.6859038926045,
			"y": 561.4127089877941,
			"strokeColor": "#2f9e44",
			"backgroundColor": "transparent",
			"width": 384.65985107421875,
			"height": 135,
			"seed": 1667721810,
			"groupIds": [
				"hnbeKiVs-lqC_EII_j17j"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "destroy right away\nafter create actual \ndoing-job thread",
			"rawText": "destroy right away\nafter create actual \ndoing-job thread",
			"textAlign": "center",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "destroy right away\nafter create actual \ndoing-job thread",
			"lineHeight": 1.25,
			"baseline": 122
		},
		{
			"type": "rectangle",
			"version": 26,
			"versionNonce": 1662964235,
			"isDeleted": false,
			"id": "zSLN1OycRek59E-rZzLA6",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2599.1893974185296,
			"y": 677.4230264481114,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 1234,
			"height": 313,
			"seed": 1280170894,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "Rm5iJd2D",
					"type": "text"
				},
				{
					"id": "Nq-LPcndKHF8qfEFoPTGp",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 683,
			"versionNonce": 7825445,
			"isDeleted": false,
			"id": "Rm5iJd2D",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2594.1893974185296,
			"y": 682.7230264481113,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 1223.4375,
			"height": 302.4,
			"seed": 405372498,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "AsyncLoadingModelCVs[stdPath];\nAsyncLoadingModelCVMutexs[stdPath];\n\nauto Task = FFunctionGraphTask::CreateAndDispatchWhenReady\n(.....);\nAsyncLoadingModelTasks.emplace(stdPath, task);\nAsyncLoadingModelCVs[stdPath].notify_all();",
			"rawText": "AsyncLoadingModelCVs[stdPath];\nAsyncLoadingModelCVMutexs[stdPath];\n\nauto Task = FFunctionGraphTask::CreateAndDispatchWhenReady\n(.....);\nAsyncLoadingModelTasks.emplace(stdPath, task);\nAsyncLoadingModelCVs[stdPath].notify_all();",
			"textAlign": "left",
			"verticalAlign": "middle",
			"containerId": "zSLN1OycRek59E-rZzLA6",
			"originalText": "AsyncLoadingModelCVs[stdPath];\nAsyncLoadingModelCVMutexs[stdPath];\n\nauto Task = FFunctionGraphTask::CreateAndDispatchWhenReady\n(.....);\nAsyncLoadingModelTasks.emplace(stdPath, task);\nAsyncLoadingModelCVs[stdPath].notify_all();",
			"lineHeight": 1.2,
			"baseline": 293
		},
		{
			"type": "arrow",
			"version": 411,
			"versionNonce": 500181536,
			"isDeleted": false,
			"id": "Nq-LPcndKHF8qfEFoPTGp",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -1344.83300133252,
			"y": 830.5345024753503,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 205.31468531468545,
			"height": 1.539080363571884,
			"seed": 1437206098,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125207672,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "zSLN1OycRek59E-rZzLA6",
				"gap": 20.356396086009454,
				"focus": -0.050682813662654216
			},
			"endBinding": {
				"elementId": "ZR0Im0-qxo6dGJtnZ4cy6",
				"gap": 6.839105339107391,
				"focus": 0.13451883173419363
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					205.31468531468545,
					1.539080363571884
				]
			]
		},
		{
			"type": "arrow",
			"version": 416,
			"versionNonce": 1610685317,
			"isDeleted": false,
			"id": "b9ByDjKLWJ0B_jsXnizT5",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2874.7009112004303,
			"y": 1209.511551076674,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 280.75757575757643,
			"height": 55.73007166114303,
			"seed": 499465938,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "hSVKxJTpLS0bo-dIni2qm",
				"focus": -0.2777373523768976,
				"gap": 1.1601176601157022
			},
			"endBinding": {
				"elementId": "uZ19kG93az1MXc-TIoYPt",
				"focus": -0.29817989236382414,
				"gap": 11.531915838068812
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					280.75757575757643,
					55.73007166114303
				]
			]
		},
		{
			"type": "rectangle",
			"version": 1287,
			"versionNonce": 1892944715,
			"isDeleted": false,
			"id": "c4T5yqYjW7AZj6qIjBmtM",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": 27.571816072296997,
			"y": 1187.3574586825443,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 470.909090909091,
			"height": 201.81818181818176,
			"seed": 763499214,
			"groupIds": [
				"7qN996Xh_I1aktL6AKdP8",
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "wDczcNizUpRo49r1P_QiA",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 1284,
			"versionNonce": 1052599013,
			"isDeleted": false,
			"id": "nM0X1tjQ",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": 139.1236751476697,
			"y": 1256.4483677734536,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 253.25991821289062,
			"height": 90,
			"seed": 533226254,
			"groupIds": [
				"7qN996Xh_I1aktL6AKdP8",
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Actual Spread\nThread",
			"rawText": "Actual Spread\nThread",
			"textAlign": "center",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "Actual Spread\nThread",
			"lineHeight": 1.25,
			"baseline": 77
		},
		{
			"type": "rectangle",
			"version": 271,
			"versionNonce": 543844843,
			"isDeleted": false,
			"id": "uZ19kG93az1MXc-TIoYPt",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2582.411419604785,
			"y": 1071.4483677734531,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 1052.1818181818182,
			"height": 415.0000000000004,
			"seed": 1316660366,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "b9ByDjKLWJ0B_jsXnizT5",
					"type": "arrow"
				},
				{
					"id": "PBfMve-gw_W4nbikzaAXs",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 350,
			"versionNonce": 1094303301,
			"isDeleted": false,
			"id": "8phwuIqX",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2518.07688776293,
			"y": 1105.5392768643621,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 833.4718017578125,
			"height": 90,
			"seed": 451748558,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "If find target Furniture has CV Mutex and CV\n    -> wait for Actual Load Task Created:",
			"rawText": "If find target Furniture has CV Mutex and CV\n    -> wait for Actual Load Task Created:",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "If find target Furniture has CV Mutex and CV\n    -> wait for Actual Load Task Created:",
			"lineHeight": 1.25,
			"baseline": 77
		},
		{
			"type": "rectangle",
			"version": 144,
			"versionNonce": 1459352715,
			"isDeleted": false,
			"id": "_W_1CkbzGMBkT5ljEtGpU",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2528.3372748367938,
			"y": 1225.9938223189076,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 935,
			"height": 226,
			"seed": 98609998,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "mLtFZtL5",
					"type": "text"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 316,
			"versionNonce": 508800421,
			"isDeleted": false,
			"id": "mLtFZtL5",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2523.3372748367938,
			"y": 1230.9938223189076,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 907.03125,
			"height": 215.99999999999997,
			"seed": 1366425106,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "std::unique_lock<std::mutex>\nlock(FurnitureCVMutex);\nwhile(!TaskArr.find(FurnitureLoadingPath))\n    FurnitureCV.wait();\nauto PreTask = TaskArr.find(...) -> second;",
			"rawText": "std::unique_lock<std::mutex> lock(FurnitureCVMutex);\nwhile(!TaskArr.find(FurnitureLoadingPath))\n    FurnitureCV.wait();\nauto PreTask = TaskArr.find(...) -> second;",
			"textAlign": "left",
			"verticalAlign": "middle",
			"containerId": "_W_1CkbzGMBkT5ljEtGpU",
			"originalText": "std::unique_lock<std::mutex> lock(FurnitureCVMutex);\nwhile(!TaskArr.find(FurnitureLoadingPath))\n    FurnitureCV.wait();\nauto PreTask = TaskArr.find(...) -> second;",
			"lineHeight": 1.2,
			"baseline": 207
		},
		{
			"type": "rectangle",
			"version": 252,
			"versionNonce": 1682123563,
			"isDeleted": false,
			"id": "S-151XetTI56aCNBKizO-",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -1302.8827293822476,
			"y": 1122.3574586825437,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 1106.7272727272725,
			"height": 369.54545454545496,
			"seed": 1812181458,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"id": "PBfMve-gw_W4nbikzaAXs",
					"type": "arrow"
				},
				{
					"id": "wDczcNizUpRo49r1P_QiA",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "arrow",
			"version": 674,
			"versionNonce": 1429778693,
			"isDeleted": false,
			"id": "PBfMve-gw_W4nbikzaAXs",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -1525.7615172610354,
			"y": 1286.8650688223056,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 221.0101010101007,
			"height": 4.5393426506668675,
			"seed": 1514085262,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "uZ19kG93az1MXc-TIoYPt",
				"focus": -0.013652840015756049,
				"gap": 4.468084161931415
			},
			"endBinding": {
				"elementId": "ROvTOdfc",
				"focus": 0.47531856601545963,
				"gap": 23.636363636364422
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					221.0101010101007,
					4.5393426506668675
				]
			]
		},
		{
			"type": "rectangle",
			"version": 160,
			"versionNonce": 1017810379,
			"isDeleted": false,
			"id": "ETTFNjhsmvcbzrO5VqFfY",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2426.9736384731577,
			"y": 1393.4180647431497,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 158.18181818181887,
			"height": 60.00000000000001,
			"seed": 532484498,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 204,
			"versionNonce": 593905765,
			"isDeleted": false,
			"id": "lUBB2GIe",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -1272.1141275312177,
			"y": 1145.539276864362,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 483.37188720703125,
			"height": 45,
			"seed": 754075922,
			"groupIds": [
				"8K2iNj-D53D5_zaqrsL9j",
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 1,
			"text": "Create Task with PreTask",
			"rawText": "Create Task with PreTask",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": null,
			"originalText": "Create Task with PreTask",
			"lineHeight": 1.25,
			"baseline": 32
		},
		{
			"type": "rectangle",
			"version": 186,
			"versionNonce": 1665965163,
			"isDeleted": false,
			"id": "ZHGpHG8oBFGzaQmBG5uDV",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -950.6100021095201,
			"y": 1145.5392768643621,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 167.27272727272725,
			"height": 45.45454545454527,
			"seed": 386118606,
			"groupIds": [
				"8K2iNj-D53D5_zaqrsL9j",
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false
		},
		{
			"type": "arrow",
			"version": 2521,
			"versionNonce": 984216517,
			"isDeleted": false,
			"id": "wDczcNizUpRo49r1P_QiA",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -177.8827293822476,
			"y": 1311.1359707335487,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 198.18181818181847,
			"height": 0.3151937088559862,
			"seed": 616332942,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1712906132576,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "S-151XetTI56aCNBKizO-",
				"focus": 0.01667973061656194,
				"gap": 18.27272727272748
			},
			"endBinding": {
				"elementId": "c4T5yqYjW7AZj6qIjBmtM",
				"focus": -0.23271944510882572,
				"gap": 7.272727272726115
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					198.18181818181847,
					0.3151937088559862
				]
			]
		},
		{
			"type": "text",
			"version": 217,
			"versionNonce": 334747403,
			"isDeleted": false,
			"id": "ROvTOdfc",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -1281.1150526145702,
			"y": 1250.9938223189074,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 1040.8359375,
			"height": 215.99999999999997,
			"seed": 130320270,
			"groupIds": [
				"20OZ2P-9Z0Ek5gyth0dB4"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "PBfMve-gw_W4nbikzaAXs",
					"type": "arrow"
				}
			],
			"updated": 1712906132576,
			"link": "[[]]",
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "📍FFunctionGraphTask::CreateAndDispatchWhenReady(\n    [[]]{...}, \n    TStatId(), PreTask, \n    ENamedThreads::GameThread);\n)",
			"rawText": "FFunctionGraphTask::CreateAndDispatchWhenReady(\n    [](){...}, \n    TStatId(), PreTask, \n    ENamedThreads::GameThread);\n)",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "📍FFunctionGraphTask::CreateAndDispatchWhenReady(\n    [[]]{...}, \n    TStatId(), PreTask, \n    ENamedThreads::GameThread);\n)",
			"lineHeight": 1.2,
			"baseline": 207
		},
		{
			"type": "line",
			"version": 164,
			"versionNonce": 1435703264,
			"isDeleted": false,
			"id": "B1n2aQ7UbVBDXHiqr-a4p",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3443.465118835242,
			"y": 2724.8433396554547,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 697.1428571428573,
			"height": 215.71428571428578,
			"seed": 72341445,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					224.28571428571468,
					215.71428571428578
				],
				[
					697.1428571428573,
					7.142857142856883
				]
			]
		},
		{
			"type": "text",
			"version": 78,
			"versionNonce": 1387451936,
			"isDeleted": false,
			"id": "oRZ7fqqL",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3550.6079759780982,
			"y": 2700.5576253697404,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 72,
			"height": 43.199999999999996,
			"seed": 187249093,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "轨迹",
			"rawText": "轨迹",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "轨迹",
			"lineHeight": 1.2,
			"baseline": 34
		},
		{
			"type": "ellipse",
			"version": 69,
			"versionNonce": 119872480,
			"isDeleted": false,
			"id": "OgsMlVkk7gZP1P2JPV-uf",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3361.322261692385,
			"y": 2844.1290539411693,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 10.000000000000002,
			"height": 12.857142857142662,
			"seed": 456578821,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"id": "-HxjqAfTMgar9ErRlc87_",
					"type": "arrow"
				},
				{
					"id": "vz_pHq2Qms_LfggoAVVtw",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "ellipse",
			"version": 67,
			"versionNonce": 1043534368,
			"isDeleted": false,
			"id": "JifFy70QrBHW0MDVT3qCd",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3111.322261692385,
			"y": 2906.9861967983124,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 10.000000000000002,
			"height": 12.857142857142662,
			"seed": 2043449611,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"id": "4S5-JjBB9wX-9DLPd1Zzw",
					"type": "arrow"
				},
				{
					"id": "UJRGZoYwRAOMVwrSGtqpi",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "ellipse",
			"version": 66,
			"versionNonce": 1071030240,
			"isDeleted": false,
			"id": "kqzqWB62XBPajxZl_ojnK",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2917.0365474066703,
			"y": 2812.7004825125987,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 10.000000000000002,
			"height": 12.857142857142662,
			"seed": 739693541,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"id": "IlEIKFt0U6-7kXgkUbiWA",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "arrow",
			"version": 547,
			"versionNonce": 1179373088,
			"isDeleted": false,
			"id": "-HxjqAfTMgar9ErRlc87_",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3243.970877913903,
			"y": 3069.4719110840265,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 102.35747268513342,
			"height": 203.14234788910335,
			"seed": 192264773,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "tEq1S9L4",
				"focus": -0.12245593246590329,
				"gap": 11.085714285714403
			},
			"endBinding": {
				"elementId": "OgsMlVkk7gZP1P2JPV-uf",
				"focus": -0.3435807526754169,
				"gap": 12.660648991291549
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-102.35747268513342,
					-203.14234788910335
				]
			]
		},
		{
			"type": "arrow",
			"version": 706,
			"versionNonce": 1874306016,
			"isDeleted": false,
			"id": "4S5-JjBB9wX-9DLPd1Zzw",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3166.8063487983563,
			"y": 3065.347313064079,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 58.79554120255352,
			"height": 138.98855583015074,
			"seed": 306865733,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "tEq1S9L4",
				"focus": 0.0036738113950520843,
				"gap": 15.210312305661773
			},
			"endBinding": {
				"elementId": "JifFy70QrBHW0MDVT3qCd",
				"focus": -0.6653690970460483,
				"gap": 6.651418301767452
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					58.79554120255352,
					-138.98855583015074
				]
			]
		},
		{
			"type": "arrow",
			"version": 702,
			"versionNonce": 1139608096,
			"isDeleted": false,
			"id": "IlEIKFt0U6-7kXgkUbiWA",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3063.6197065456054,
			"y": 3076.775884492651,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 149.00219646727692,
			"height": 235.5955963707529,
			"seed": 1966958917,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "tEq1S9L4",
				"focus": 0.288460086985732,
				"gap": 3.78174087708976
			},
			"endBinding": {
				"elementId": "kqzqWB62XBPajxZl_ojnK",
				"focus": -1.7635964509579298,
				"gap": 15.792568275957152
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					149.00219646727692,
					-235.5955963707529
				]
			]
		},
		{
			"type": "text",
			"version": 306,
			"versionNonce": 81274848,
			"isDeleted": false,
			"id": "tEq1S9L4",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3530.6079759780996,
			"y": 3080.557625369741,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 693.84375,
			"height": 43.199999999999996,
			"seed": 208080587,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "-HxjqAfTMgar9ErRlc87_",
					"type": "arrow"
				},
				{
					"id": "IlEIKFt0U6-7kXgkUbiWA",
					"type": "arrow"
				},
				{
					"id": "4S5-JjBB9wX-9DLPd1Zzw",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "线性运动下：位移在25%，50%，75%的位置",
			"rawText": "线性运动下：位移在25%，50%，75%的位置",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "线性运动下：位移在25%，50%，75%的位置",
			"lineHeight": 1.2,
			"baseline": 34
		},
		{
			"type": "arrow",
			"version": 121,
			"versionNonce": 1913046560,
			"isDeleted": false,
			"id": "vz_pHq2Qms_LfggoAVVtw",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3346.322261692385,
			"y": 2836.2719110840267,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 60,
			"height": 78.57142857142844,
			"seed": 962887883,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "OgsMlVkk7gZP1P2JPV-uf",
				"focus": -0.12973890370336705,
				"gap": 11.491550526792603
			},
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					60,
					-78.57142857142844
				]
			]
		},
		{
			"type": "arrow",
			"version": 115,
			"versionNonce": 726150112,
			"isDeleted": false,
			"id": "UJRGZoYwRAOMVwrSGtqpi",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3100.607975978099,
			"y": 2891.9861967983124,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 50,
			"height": 115.71428571428578,
			"seed": 1146934949,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "JifFy70QrBHW0MDVT3qCd",
				"focus": 2.6178466575915125,
				"gap": 15.844001657672031
			},
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-50,
					-115.71428571428578
				]
			]
		},
		{
			"type": "arrow",
			"version": 121,
			"versionNonce": 763953696,
			"isDeleted": false,
			"id": "gL-A0ySgqvzOj890M9oLv",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -2913.465118835242,
			"y": 2796.2719110840267,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 71.42857142857156,
			"height": 77.14285714285734,
			"seed": 151961899,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": {
				"elementId": "2tMkgyo_qH_3xRQiiqVOq",
				"focus": -0.6582365003417723,
				"gap": 9.899118210394477
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-71.42857142857156,
					-77.14285714285734
				]
			]
		},
		{
			"type": "text",
			"version": 176,
			"versionNonce": 219656160,
			"isDeleted": false,
			"id": "Meflpx2B",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3416.3222616923854,
			"y": 2587.700482512598,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 693.84375,
			"height": 43.199999999999996,
			"seed": 443718885,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "线性运动下：旋转在25%，50%，75%的角度",
			"rawText": "线性运动下：旋转在25%，50%，75%的角度",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "线性运动下：旋转在25%，50%，75%的角度",
			"lineHeight": 1.2,
			"baseline": 34
		},
		{
			"type": "line",
			"version": 196,
			"versionNonce": 895729184,
			"isDeleted": false,
			"id": "iI8q1JRy1MFz8mLMeJE4B",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3450.3869938352423,
			"y": 3529.6719110840286,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 697.1428571428573,
			"height": 215.71428571428578,
			"seed": 1093026731,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					224.28571428571468,
					215.71428571428578
				],
				[
					697.1428571428573,
					7.142857142856883
				]
			]
		},
		{
			"type": "text",
			"version": 110,
			"versionNonce": 307672032,
			"isDeleted": false,
			"id": "QPV1wU6d",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3557.5298509780982,
			"y": 3505.386196798314,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 72,
			"height": 43.199999999999996,
			"seed": 781620811,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "轨迹",
			"rawText": "轨迹",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "轨迹",
			"lineHeight": 1.2,
			"baseline": 34
		},
		{
			"type": "ellipse",
			"version": 168,
			"versionNonce": 1787230752,
			"isDeleted": false,
			"id": "0pXSmZrhubBxVIS_NumYH",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3409.672708120957,
			"y": 3583.2433396554575,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 10.000000000000002,
			"height": 12.857142857142662,
			"seed": 1000576235,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"id": "ILc6n5k0rzulMFRGFNrcn",
					"type": "arrow"
				},
				{
					"id": "WZb5mvqopaNXyLKJRPoXd",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "arrow",
			"version": 909,
			"versionNonce": 555038688,
			"isDeleted": false,
			"id": "ILc6n5k0rzulMFRGFNrcn",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3216.7029561687705,
			"y": 3874.300482512601,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 176.34815074522385,
			"height": 270.2548908212839,
			"seed": 458201291,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "CUOB1xgb",
				"focus": -0.12196496270606044,
				"gap": 11.085714285713948
			},
			"endBinding": {
				"elementId": "0pXSmZrhubBxVIS_NumYH",
				"focus": -0.34358075267547766,
				"gap": 12.630443455778517
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-176.34815074522385,
					-270.2548908212839
				]
			]
		},
		{
			"type": "text",
			"version": 408,
			"versionNonce": 266516000,
			"isDeleted": false,
			"id": "CUOB1xgb",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3537.529850978099,
			"y": 3885.386196798315,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 783.28125,
			"height": 43.199999999999996,
			"seed": 1681369259,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "ILc6n5k0rzulMFRGFNrcn",
					"type": "arrow"
				},
				{
					"id": "HOSa8dc2OKGen5w-fTB79",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "自动平滑运动下：时间到25%时，位移可能的位置",
			"rawText": "自动平滑运动下：时间到25%时，位移可能的位置",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "自动平滑运动下：时间到25%时，位移可能的位置",
			"lineHeight": 1.2,
			"baseline": 34
		},
		{
			"type": "text",
			"version": 144,
			"versionNonce": 1566784480,
			"isDeleted": false,
			"id": "HKGhhHQG",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3964.8936902638125,
			"y": 3270.557625369743,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 360,
			"height": 86.39999999999999,
			"seed": 1899626789,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "只改变位移的运动模式\n不改变旋转的",
			"rawText": "只改变位移的运动模式\n不改变旋转的",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "只改变位移的运动模式\n不改变旋转的",
			"lineHeight": 1.2,
			"baseline": 77
		},
		{
			"type": "arrow",
			"version": 226,
			"versionNonce": 174518816,
			"isDeleted": false,
			"id": "HOSa8dc2OKGen5w-fTB79",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3579.179404549527,
			"y": 3100.5576253697436,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 220,
			"height": 805.7142857142853,
			"seed": 17453093,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": {
				"elementId": "CUOB1xgb",
				"focus": -1.0192041657332538,
				"gap": 15.935267857142208
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-194.28571428571422,
					211.42857142857156
				],
				[
					25.71428571428578,
					805.7142857142853
				]
			]
		},
		{
			"type": "arrow",
			"version": 207,
			"versionNonce": 1766899680,
			"isDeleted": false,
			"id": "WZb5mvqopaNXyLKJRPoXd",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3400.980218245166,
			"y": 3580.847610429422,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 55.639624954663304,
			"height": 72.86141363110664,
			"seed": 80816491,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "0pXSmZrhubBxVIS_NumYH",
				"focus": -0.4347127307541728,
				"gap": 3.3856511865742975
			},
			"endBinding": {
				"elementId": "C-77uqYdwVw_rDNvtnHTc",
				"focus": 1.0834780049123922,
				"gap": 4.364486239226856
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					55.639624954663304,
					-72.86141363110664
				]
			]
		},
		{
			"type": "text",
			"version": 183,
			"versionNonce": 553889312,
			"isDeleted": false,
			"id": "qMDNPGsn",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3344.8936902638125,
			"y": 3299.986196798315,
			"strokeColor": "#1971c2",
			"backgroundColor": "transparent",
			"width": 783.28125,
			"height": 43.199999999999996,
			"seed": 190545803,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "时间在25%的时候，旋转在线性模式下的旋转没变",
			"rawText": "时间在25%的时候，旋转在线性模式下的旋转没变",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "时间在25%的时候，旋转在线性模式下的旋转没变",
			"lineHeight": 1.2,
			"baseline": 34
		},
		{
			"type": "ellipse",
			"version": 76,
			"versionNonce": 619561952,
			"isDeleted": false,
			"id": "g0gaZ6joRtgJYROkEPyS_",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3410.8936902638125,
			"y": 2719.986196798315,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 206,
			"height": 216,
			"seed": 330532613,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"id": "mTYX_0l42z0euDM6f7B0T",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "arrow",
			"version": 226,
			"versionNonce": 1017702944,
			"isDeleted": false,
			"id": "mTYX_0l42z0euDM6f7B0T",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3338.8936902638125,
			"y": 2935.986196798315,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 16,
			"height": 526,
			"seed": 996700069,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"startBinding": {
				"elementId": "g0gaZ6joRtgJYROkEPyS_",
				"focus": 0.26893924989853535,
				"gap": 4.7659174344878465
			},
			"endBinding": {
				"elementId": "aYwwAroEfeLR6MJH2Eqa3",
				"focus": 0.004575177251669418,
				"gap": 8.07527834179028
			},
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": "arrow",
			"points": [
				[
					0,
					0
				],
				[
					-16,
					526
				]
			]
		},
		{
			"type": "ellipse",
			"version": 119,
			"versionNonce": 1850361824,
			"isDeleted": false,
			"id": "aYwwAroEfeLR6MJH2Eqa3",
			"fillStyle": "hachure",
			"strokeWidth": 4,
			"strokeStyle": "dotted",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3461.8936902638125,
			"y": 3469.986196798315,
			"strokeColor": "#f08c00",
			"backgroundColor": "transparent",
			"width": 206,
			"height": 216,
			"seed": 1641856907,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"id": "mTYX_0l42z0euDM6f7B0T",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "diamond",
			"version": 251,
			"versionNonce": 675718688,
			"isDeleted": false,
			"id": "2tMkgyo_qH_3xRQiiqVOq",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3352.8936902638125,
			"y": 2641.986196798315,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 418.0000000000001,
			"height": 108,
			"seed": 1790401611,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"type": "text",
					"id": "faFFkZRs"
				},
				{
					"id": "gL-A0ySgqvzOj890M9oLv",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 182,
			"versionNonce": 1635142624,
			"isDeleted": false,
			"id": "faFFkZRs",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3215.8936902638125,
			"y": 2674.3861967983153,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 144,
			"height": 43.199999999999996,
			"seed": 1725147403,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "观测物体",
			"rawText": "观测物体",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "2tMkgyo_qH_3xRQiiqVOq",
			"originalText": "观测物体",
			"lineHeight": 1.2,
			"baseline": 34
		},
		{
			"type": "diamond",
			"version": 309,
			"versionNonce": 1355604512,
			"isDeleted": false,
			"id": "C-77uqYdwVw_rDNvtnHTc",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3327.8936902638125,
			"y": 3453.986196798315,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 418.0000000000001,
			"height": 108,
			"seed": 273250347,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [
				{
					"type": "text",
					"id": "874OoTKB"
				},
				{
					"id": "WZb5mvqopaNXyLKJRPoXd",
					"type": "arrow"
				}
			],
			"updated": 1714125221579,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 240,
			"versionNonce": 411160544,
			"isDeleted": false,
			"id": "874OoTKB",
			"fillStyle": "hachure",
			"strokeWidth": 2,
			"strokeStyle": "solid",
			"roughness": 2,
			"opacity": 100,
			"angle": 0,
			"x": -3190.8936902638125,
			"y": 3486.3861967983153,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 144,
			"height": 43.199999999999996,
			"seed": 207567563,
			"groupIds": [
				"vrToY5sSLFzJJ1978IJqP"
			],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1714125221579,
			"link": null,
			"locked": false,
			"fontSize": 36,
			"fontFamily": 3,
			"text": "观测物体",
			"rawText": "观测物体",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "C-77uqYdwVw_rDNvtnHTc",
			"originalText": "观测物体",
			"lineHeight": 1.2,
			"baseline": 34
		}
	],
	"appState": {
		"theme": "light",
		"viewBackgroundColor": "#fdf8f6",
		"currentItemStrokeColor": "#1e1e1e",
		"currentItemBackgroundColor": "transparent",
		"currentItemFillStyle": "hachure",
		"currentItemStrokeWidth": 2,
		"currentItemStrokeStyle": "solid",
		"currentItemRoughness": 2,
		"currentItemOpacity": 100,
		"currentItemFontFamily": 3,
		"currentItemFontSize": 36,
		"currentItemTextAlign": "left",
		"currentItemStartArrowhead": null,
		"currentItemEndArrowhead": "arrow",
		"scrollX": 4922.0695450080275,
		"scrollY": -1777.5234494098183,
		"zoom": {
			"value": 0.44999999999999996
		},
		"currentItemRoundness": "round",
		"gridSize": null,
		"gridColor": {
			"Bold": "#EAB49EFF",
			"Regular": "#F7E1D9FF"
		},
		"currentStrokeOptions": null,
		"previousGridSize": null,
		"frameRendering": {
			"enabled": true,
			"clip": true,
			"name": true,
			"outline": true
		}
	},
	"files": {}
}
```
%%