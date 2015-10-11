#pragma once
#include "stdafx.h"

#define SNAPSHOTTYPE_TEXT 2162865
#define PACKET_SNAPSHOP 0x21000B6;




const byte COMMONPLACE_ACTION	= 0x00;
const byte COMMONPLACE_ALPHA	= 0x01;
const byte COMMONPLACE_QUAKE	= 0x02;
const byte CT_WANTED_REQ_LIST   = 0x00;		// Core->Trans 리스트 요청 
const byte CT_WANTED_SET		= 0x01;		// Core->Trans 현상금 설정 
const byte ADD_PLAYER_ENEMY		= 0x00;		// 플레이어 적 추가 
const byte DEL_PLAYER_ENEMY		= 0x01;		// 플레이어 적 제거 
const byte GC_WINGUILD			= 0x00;		// 이긴 길드 정보
const byte GC_IN_WINDOW			= 0x01;		// 대전 신청 창 띄움
const byte GC_IN_APP			= 0x02;		// 대전 신청
const byte GC_IN_COMPLETE		= 0x03;		// 길드대전 신청 완료
const byte GC_REQUEST_STATUS	= 0x04;		// 대전 신청 현황
const byte GC_SELECTPLAYER		= 0x05;		// 길드대전 선택 캐릭터 창 띄움
const byte GC_SELECTWARPOS		= 0x06;		// 대전위치 윈도우 띄움
const byte GC_BESTPLAYER		= 0x07;		// BEST Player 정보
const byte GC_ISREQUEST			= 0x08;		// 신청중인지?
const byte GC_USERSTATE			= 0x10;		// 유저상태
const byte GC_WARPLAYERLIST		= 0x11;		// 전쟁유저 정보
const byte GC_GUILDSTATUS		= 0x20;		// 자신의 길드 상황
const byte GC_GUILDPRECEDENCE	= 0x21;		// 길드 순위
const byte GC_PLAYERPRECEDENCE	= 0x22;		// 개인 순위
const byte GC_GCSTATE			= 0x30;		// 대전 상황	
const byte GC_NEXTTIMESTATE		= 0x31;		// 대전시 다음 시간과 상태 넘겨주기
const byte GC_ENTERTIME			= 0x32;		// 대전시 들어갈수 있는 시간
const byte GC_DIAGMESSAGE		= 0x33;		// 다이얼 로그 메세지
const byte GC_TELE				= 0x34;		// 텔레포트
const byte GC_LOG				= 0x35;		// 대전 로그( 대전이 끝나면 나오게~ )
const byte GC_LOG_REALTIME		= 0x36;		// 대전 로그( 실시간으로 채팅창에 나오게~ )
const byte GC_GETPENYAGUILD		= 0x40;		// 길드 신청금액 및 보상
const byte GC_GETPENYAPLAYER	= 0x41;		// 베스트 플레이어 보상
const byte GC_PLAYERPOINT		= 0x42;		// 길드대전 플레이어 포인트
const byte SOMMON_FRIEND			= 0x00;		// 친구 소환
const byte SOMMON_FRIEND_CONFIRM	= 0x01;		// 친구 소환 확인
const byte SOMMON_PARTY_CONFIRM		= 0x10;		// 파티 소환
const byte LOG_SKILLPOINT_GET_QUEST	= 0x00;		// 스킬포인트 얻기 - 퀘스트
const byte LOG_SKILLPOINT_GET_HUNT	= 0x01;		// 스킬포인트 얻기 - 몬스터
const byte LOG_SKILLPOINT_USE		= 0x10;		// 스킬포인트 쓰기 - 스킬레벨업
const byte PK_PINK					= 0x00;		// 핑크상태 전송
const byte PK_PROPENSITY			= 0x01;		// 카오성향 전송
const byte PK_PKVALUE				= 0x02;		// 카오수치 전송
const byte ANGEL_INFO				= 0x01;		// 엔젤 정보 주기(경험치, 레벨)
const byte TEXT_GENERAL				= 0x01;		// OnText
const byte TEXT_DIAG				= 0x02;		// OnDiagText
const byte MINIGAME_KAWIBAWIBO_RESUTLT		= 0x01;		// 가위바위보 결과값
const byte MINIGAME_REASSEMBLE_RESULT		= 0x02;		// 퍼즐 결과
const byte MINIGAME_REASSEMBLE_OPENWND		= 0x03;		// 퍼즐창 열때 카드아이템 값들을 얻기위해...
const byte MINIGAME_ALPHABET_OPENWND		= 0x04;		// 알파벳 창 열때 공개 글자와 위치
const byte MINIGAME_ALPHABET_RESULT			= 0x05;		// 알파벳 맞추기 결과
const byte MINIGAME_FIVESYSTEM_OPENWND		= 0x06;		// 오곱 창 열때 최소, 최대, 배수
const byte MINIGAME_FIVESYSTEM_RESULT		= 0x07;		// 오곱 결과
const byte ULTIMATE_MAKEITEM				= 0x01;		// 빛나는 오리칼쿰 생성
const byte ULTIMATE_TRANSWEAPON				= 0x02;		// 무기 변환(일반->유니크, 유니크->얼터멋)
const byte ULTIMATE_MAKEGEM					= 0x03;		// 보석 생성(아이템 쪼개기)
const byte ULTIMATE_SETGEM					= 0x04;		// 보석 합성
const byte ULTIMATE_REMOVEGEM				= 0x05;		// 보석 제거
const byte ULTIMATE_ENCHANTWEAPON			= 0x06;		// 얼터멋 웨폰 제련
const byte EXCHANGE_RESULT					= 0x01;		// 교환 스크립트 결과
const byte LEGENDSKILL_RESULT					= 0x01;		// legend 스킬 결과
const byte GI_LOG_VIEW_ITEM_ADD					= 0x01;		// 길드창고 아이템추가 로그
const byte GI_LOG_VIEW_ITEM_REMOVE					= 0x02;		// 길드창고 아이템제거 로그
const byte GI_LOG_VIEW_MONEY_ADD					= 0x03;		// 길드창고 돈추가 로그
const byte GI_LOG_VIEW_MONEY_REMOVE					= 0x04;		// 길드창고 돈추가 로그
const byte SECRETROOM_GUILDLIST		= 0x01;
const byte SECRETROOM_KILLCOUNT		= 0x02;
const byte SECRETROOM_WARSTATE		= 0x03;