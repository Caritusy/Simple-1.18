#pragma once
#include "../Utils/easylogging++.h"
#include <bitset>
#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "BlockLegacy.h"
#include "C_EntityList.h"
#include "CInventory.h"
#include "../SDK/TextHolder.h"

class GameMode;
#pragma pack(push, 4)
class Level {
private:
	char pad_0x0[0x6AC];
public:
	int levelTicks; //0x6B0
private:
	char pad_0x6B0[0x344]; //6B0
public:
	int rayHitType;    //0x9F4
	int blockSide;     //0x9F8
private:
	char pad_[0xC];
public:
	Vec3 block;   //0xA08
	Vec3 rayHitVec;      //0xA14
public:
	Entity* getEntity();
};

class Entity {
private:
	char pad_0x0[0x10c];
public:
	union {
		struct {
			float pitch; // 0x138
			float yaw;   // 0x13C
		};
		Vec2 viewAngles;
	};
	union {
		struct {
			float pitch2;  // 0x140
			float yaw2;    // 0x144
		};
		Vec2 viewAngles2;
	};
private:
	char pad_0x120[0x10]; //128
public:
	Vec3 eyePos0; //0x12C
private:
	char pad_0x130[0x54];
public:
	float fallDistance; //190
	bool onGround;   //194
private:
	char pad_0x198[0x58];
public:
	float stepHeight;  // 0X1f0
private:
	char pad_0x1f0[0x10]; //0x1f1
public:
	Vec3 slowdownFactor;  //0x204
private:
	char pad_0x260[0x50]; //0x20D
public:
	int32_t ticksAlive;  // 0x260
	int32_t hurttime;  // 0x264
private:
	char pad_0x261[0xC4];
public:
	BlockSource* region;   // 0x32c
	void* dimension;  // 0x330
	Level* level;          // 0x334
private:
	char pad_0x335[0x64];   //39c=entittypeid
public:
	__int32 Entittypeid;
private:
	char pad_39c[0x18]; //
public:
	char entityId[16];   //0x3b8
private:
	char pad_0x3bc[0x80];  //3c8
public:
	AABB aabb;  //448
	float width;        //0x0460
	float height;       //0x464
	Vec3 currentPos;  // 0x468
	Vec3 oldPos;      // 0x474
	Vec3 velocity;    // 0x480
private:
	char pad_0x48c[0x44];  //0x48c
public:
	int EntityRuntimeid; //0x4d0
private:
	char pad_0x4bc[0x34c];
public:
	float bodyYaw;                    // 0x820
	float oldBodyYaw;                 // 0x824
	float yawUnused1;                 // 0x828
	float yawUnused2;                 // 0x82c
private:
	char pad_830[0x29c];   //830
public:
	TextHolder playerName;  //0xACc
private:
	char pad_0xad8[0x78];  //0xb58
public:
	bool canFly;  //0xB5c
private:
	char pad_0xB69[0x16E0];
public:
	int gamemode;//2240
private:
	virtual void function_0();   // 0
	virtual void function_1();   // 1
	virtual void function_2();   // 2
	virtual void function_3();   // 3
	virtual void function_4();   // 4
	virtual void function_5();   // 5
	virtual void function_6();   // 6
	virtual void function_7();   // 7
	virtual void function_8();   // 8
	virtual void function_9();   // 9
	virtual void function_10();   // 10
	virtual void function_11();   // 11
	virtual void function_12();   // 12
	virtual void function_13();  // 13
	virtual void function_14();   // 14
	virtual void function_15();  // 15
	virtual void function_16();   // 16
	virtual void function_17();   // 17
	virtual void function_18();   // 18
	virtual void function_19();   // 19
	virtual void function_20();   // 20
public:
	virtual void setpos(Vec3 const&);   // 21
private:
	virtual void function_22();   // 22
	virtual void function_23();   // 23
public:
	virtual Vec3* getPos(void);   // 24
	virtual Vec3* getPosOld(void);   // 25
private:
	virtual void function_26();   // 26
	virtual void function_27();   // 27
	virtual void function_28();   // 28
public:
	virtual int setRot(Vec2 const&);   // 29
private:
	virtual void function_30();   // 30
	virtual void function_31();   // 31
	virtual void function_32();   // 32
	virtual void function_33();   // 33
	virtual void function_34();   // 34
	virtual void function_35();   // 35
	virtual void function_36();   // 36
	virtual void function_37();   // 37
	virtual void function_38();   // 38
	virtual void function_39();   // 39
	virtual void function_40();   // 40
	virtual void function_41();   // 41
	virtual void function_42();   // 42
	virtual void function_43();   // 43
	virtual void function_44();   // 44
public:
	virtual int teleporTo(Vec3 const&, bool, int, int);   // 45
	virtual int tryTeleporTo(Vec3 const&, bool, bool, int, int);   // 46
private:
	virtual void function_47();   // 47
public:
	virtual int lerpMotion(Vec3 const&);   // 48
private:
	virtual void function_49();   // 49
public:
	virtual int normalTick(void);   // 50
	virtual int baseTick(void);   // 51
private:
	virtual void function_52();   // 52
	virtual void function_53();   // 53
	virtual void function_54();   // 54
	virtual void function_55();   // 55
	virtual void function_56();   // 56
	virtual void function_57();   // 57
	virtual void function_58();   // 58
	virtual void function_59();   // 59
	virtual bool isInWall(void);   // 60
	virtual void function_61();   // 61
public:
	virtual bool canShowNameTag();   // 62
private:
	virtual void function_63();   // 63
	virtual void function_64();   // 64
public:
	virtual TextHolder* GetNameTag();   // 65
private:
	virtual void function_66();   // 66
	virtual void function_67();   // 67
	virtual void function_68();   // 68
	virtual void function_69();   // 69
	virtual void function_70();   // 70
	virtual void function_71();   // 71
	virtual void function_72();   // 72
public:
	virtual bool isInWater(void);       // 73
	virtual bool isInLava(void);     // 74
private:
	virtual void function_75();   // 75
	virtual void function_76();   // 76
	virtual void function_77();   // 77
	virtual void function_78();   // 78
	virtual void function_79();   // 79
	virtual void function_80();   // 80
	virtual void function_81();   // 81
	virtual void function_82();   // 82
	virtual void function_83();   // 83
	virtual void function_84();   // 84
	virtual void function_85();   // 85
	virtual void function_86();   // 86
	virtual void function_87();   // 87
	virtual void function_88();   // 88
	virtual void function_89();   // 89
	virtual void function_90();   // 90
	virtual void function_91();   // 91
	virtual void function_92();   // 92
	virtual void function_93();   // 93
	virtual void function_94();   // 94
	virtual void function_95();   // 95
	virtual void function_96();   // 96
	virtual void function_97();   // 97
	virtual void function_98();   // 98
	virtual void function_99();   // 99
	virtual void function_100();  // 100
	virtual void function_101();  // 101
	virtual void function_102();  // 102
	virtual void function_103();  // 103
public:
	virtual bool isAlive(void);  // 104
	virtual bool isOnFire(void);  // 105
	virtual bool isOnHotBlock(void);  // 106
	virtual bool isCreativeModeAllowed(void);  // 107
private:
	virtual void function_108();  // 108
	virtual void function_109();  // 109
	virtual void function_110();  // 110
	virtual void function_111();  // 111
public:
	virtual bool isSurfaceMob();  // 112
	virtual bool isTargetable();  // 113
private:
	virtual void function_114();  // 114
	virtual void function_115();  // 115
	virtual void function_116();  // 116
	virtual void function_117();  // 117
	virtual void function_118();  // 118
	virtual void function_119();  // 119
	virtual void function_120();  // 120
	virtual void function_121();  // 121
	virtual void function_122();  // 122
	virtual void function_123();  // 123
	virtual void function_124();  // 124
	virtual void function_125();  // 125
	virtual void function_126();  // 126
	virtual void function_127();  // 127
	virtual void function_128();  // 128
	virtual void function_129();  // 129
	virtual void function_130();  // 130
	virtual void function_131();  // 131
	virtual void function_132();  // 132
	virtual void function_133();  // 133
	virtual void function_134();  // 134
	virtual void function_135();  // 135
	virtual void function_136();  // 136
	virtual void function_137();  // 137
	virtual void function_138();  // 138
	virtual void function_139();  // 139
	virtual void function_140();  // 140
	virtual void function_141();  // 141
	virtual void function_142();  // 142
	virtual void function_143();  // 143
	virtual void function_144();  // 144
	virtual void function_145();  // 145
	virtual void function_146();  // 146
	virtual void function_147();  // 147
	virtual void function_148();  // 148
	virtual void function_149();  // 149
	virtual void function_150();  // 150
	virtual void function_151();  // 151
	virtual void function_152();  // 152
	virtual void function_153();  // 153
	virtual void function_154();  // 154
	virtual void function_155();  // 155
	virtual void function_156();  // 156
	virtual void function_157();  // 157
	virtual void function_158();  // 158
	virtual void function_159();  // 159
	virtual void function_160();  // 160
	virtual void function_161();  // 161
	virtual void function_162();  // 162
	virtual void function_163();  // 163
	virtual void function_164();  // 164
	virtual void function_165();  // 165
	virtual void function_166();  // 166
	virtual void function_167();  // 167
	virtual void function_168();  // 168
	virtual void function_169();  // 169
	virtual void function_170();  // 170
public:
	virtual __int32 getEntityTypeId(void);  // 171
private:
	virtual void function_172();  // 172
	virtual void function_173();  // 173
	virtual void function_174();  // 174
	virtual void function_175();  // 175
	virtual void function_176();  // 176
	virtual void function_177();  // 177
	virtual void function_178();  // 178
	virtual void function_179();  // 179
	virtual void function_180();  // 180
	virtual void function_181();  // 181
	virtual void function_182();  // 182
	virtual void function_183();  // 183
	virtual void function_184();  // 184
	virtual void function_185();  // 185
	virtual void function_186();  // 186
	virtual void function_187();  // 187
	virtual void function_188();  // 188
	virtual void function_189();  // 189
	virtual void function_190();  // 190
	virtual void function_191();  // 191
	virtual void function_192();  // 192
	virtual void function_193();  // 193
	virtual void function_194();  // 194
	virtual void function_195();  // 195
	virtual void function_196();  // 196
	virtual void function_197();  // 197
	virtual void function_198();  // 198
	virtual void function_199();  // 199
	virtual void function_200();  // 200
	virtual void function_201();  // 201
	virtual void function_202();  // 202
	virtual void function_203();  // 203
	virtual void function_204();  // 204
	virtual void function_205();  // 205
	virtual void function_206();  // 206
	virtual void function_207();  // 207
	virtual void function_208();  // 208
	virtual void function_209();  // 209
	virtual void function_210();  // 210
	virtual void function_211();  // 211
	virtual void function_212();  // 212
	virtual void function_213();  // 213
	virtual void function_214();  // 214
	virtual void function_215();  // 215
	virtual void function_216();  // 216
	virtual void function_217();  // 217
	virtual void function_218();  // 218
	virtual void function_219();  // 219
	virtual void function_220();  // 220
	virtual void function_221();  // 221
	virtual void function_222();  // 222
	virtual void function_223();  // 223
	virtual void function_224();  // 224
	virtual void function_225();  // 225
	virtual void function_226();  // 226
public:
	virtual int swing(void);  // 227
private:
	virtual void function_228();  // 228
	virtual void function_229();  // 229
	virtual void function_230();  // 230
	virtual void function_231();  // 231
	virtual void function_232();  // 232
	virtual void function_233();  // 233
	virtual void function_234();  // 234
	virtual void function_235();  // 235
	virtual void function_236();  // 236
	virtual void function_237();  // 237
	virtual void function_238();  // 238
	virtual void function_239();  // 239
	virtual void function_240();  // 240
	virtual void function_241();  // 241
	virtual void function_242();  // 242
	virtual void function_243();  // 243
	virtual void function_244();  // 244
	virtual void function_245();  // 245
	virtual void function_246();  // 246
	virtual void function_247();  // 247
	virtual void function_248();  // 248
	virtual void function_249();  // 249
	virtual void function_250();  // 250
	virtual void function_251();  // 251
	virtual void function_252();  // 252
	virtual void function_253();  // 253
	virtual void function_254();  // 254
	virtual void function_255();  // 255
	virtual void function_256();  // 256
	virtual void function_257();  // 257
	virtual void function_258();  // 258
	virtual void function_259();  // 259
	virtual void function_260();  // 260
	virtual void function_261();  // 261
	virtual void function_262();  // 262
	virtual void function_263();  // 263
	virtual void function_264();  // 264
	virtual void function_265();  // 265
	virtual void function_266();  // 266
	virtual void function_267();  // 267
	virtual void function_268();  // 268
	virtual void function_269();  // 269
	virtual void function_270();  // 270
	virtual void function_271();  // 271
	virtual void function_272();  // 272
	virtual void function_273();  // 273
	virtual void function_274();  // 274
	virtual void function_275();  // 275
	virtual void function_276();  // 276
	virtual void function_277();  // 277
	virtual void function_278();  // 278
	virtual void function_279();  // 279
	virtual void function_280();  // 280
	virtual void function_281();  // 281
	virtual void function_282();  // 282
	virtual void function_283();  // 283
	virtual void function_284();  // 284
	virtual void function_285();  // 285
	virtual void function_286();  // 286
	virtual void function_287();  // 287
	virtual void function_288();  // 288
	public:

	virtual __int32 attack(Entity*);
	private:
	virtual void function_290();  // 290
	virtual void function_291();  // 291
public:
	virtual int setSprinting(bool);  // 292
	virtual __int32 getHurtSound(void);       // 293
	virtual __int64 getDeathSound(void);    // 294
private:
	virtual void function_295();  // 295
	virtual void function_296();  // 296
	virtual void function_297();  // 297
	virtual void function_298();  // 298
	virtual void function_299();  // 299
	virtual void function_300();  // 300
	virtual void function_301();  // 301
	virtual void function_302();  // 302
	virtual void function_303();  // 303
	virtual void function_304();  // 304
	virtual void function_305();  // 305
	virtual void function_306();  // 306
	virtual void function_307();  // 307
	virtual void function_308();  // 308
	virtual void function_309();  // 309
	virtual void function_310();  // 310
	virtual void function_311();  // 311
	virtual void function_312();  // 312
	virtual void function_313();  // 313
	virtual void function_314();  // 314
	virtual void function_315();  // 315
	virtual void function_316();  // 316
	virtual void function_317();  // 317
	virtual void function_318();  // 318
	virtual void function_319();  // 319
	virtual void function_320();  // 320
	virtual void function_321();  // 321
	virtual void function_322();  // 322
	virtual void function_323();  // 323
	virtual void function_324();  // 324
	virtual void function_325();  // 325
	virtual void function_326();  // 326
	virtual void function_327();  // 327
	virtual void function_328();  // 328
	virtual void function_329();  // 329
	virtual void function_330();  // 330
	virtual void function_331();  // 331
	virtual void function_332();  // 332
	virtual void function_333();  // 333
	virtual void function_334();  // 334
	virtual void function_335();  // 335
	virtual void function_336();  // 336
	virtual void function_337();  // 337
	virtual void function_338();  // 338
	virtual void function_339();  // 339
	virtual void function_340();  // 340
	virtual void function_341();  // 341
	virtual void function_342();  // 342
	virtual void function_343();  // 343
	virtual void function_344();  // 344
	virtual void function_345();  // 345
	virtual void function_346();  // 346
	virtual void function_347();  // 347
	virtual void function_348();  // 348
	virtual void function_349();  // 349
	virtual void function_350();  // 350
	virtual void function_351();  // 351
	virtual void function_352();  // 352
	virtual void function_353();  // 353
	virtual void function_354();  // 354
	virtual void function_355();  // 355
	virtual void function_356();  // 356
	virtual void function_357();  // 357
	virtual void function_358();  // 358
	virtual void function_359();  // 359
	virtual void function_360();  // 360
	virtual void function_361();  // 361
	virtual void function_362();  // 362
	virtual void function_363();  // 363
public:
	virtual int JumpFromGround(void);  // 364
private:
	virtual void function_365();  // 365
	virtual void function_366();  // 366
	virtual void function_367();  // 367
	virtual void function_368();  // 368
	virtual void function_369();  // 369
	virtual void function_370();  // 370
	virtual void function_371();  // 371
	virtual void function_372();  // 372
	virtual void function_373();  // 373
	virtual void function_374();  // 374
	virtual void function_375();  // 375
	virtual void function_376();  // 376
	virtual void function_377();  // 377
	virtual void function_378();  // 378
	virtual void function_379();  // 379
	virtual void function_380();  // 380
	virtual void function_381();  // 381
	virtual void function_382();  // 382
	virtual void function_383();  // 383
	virtual void function_384();  // 384
	virtual void function_385();  // 385
	virtual void function_386();  // 386
	virtual void function_387();  // 387
	virtual void function_388();  // 388
	virtual void function_389();  // 389
	virtual void function_390();  // 390
	virtual void function_391();  // 391
	virtual void function_392();  // 392
	virtual void function_393();  // 393
	virtual void function_394();  // 394
	virtual void function_395();  // 395
	virtual void function_396();  // 396
	virtual void function_397();  // 397
	virtual void function_398();  // 398
	virtual void function_399();  // 399
	virtual void function_400();  // 400
	virtual void function_401();  // 401
public:
	virtual __int32 openBook(int, bool, int, __int32*);                                               //402
private:
	virtual void function_403();  // 403
public:
	virtual void openInventory(void); // 404
private:
	virtual void function_405();  // 405
	virtual void function_406();  // 406
	virtual void function_407();  // 407
	virtual void function_408();  // 408
public:
	virtual __int32 displayClientMessage(TextHolder&);      // 409
private:
	virtual void function_410();  // 410
	virtual void function_411();  // 411
	virtual void function_412();  // 412
	virtual void function_413();  // 413
	virtual void function_414();  // 414
public:
	virtual __int32 getSleepTimer(void);                                                                  // 415
	virtual __int32 getPreviousTickSleepTimer(void);    //416
	virtual __int32 openSign(Vec3 const&);           // 417
	virtual void playEmote(std::string);  // 418
	virtual bool isHostingC_Player(void);   // 419
	virtual bool isLoading(void);        // 420
private:
	virtual void function_421();  // 421
	virtual void function_422();  // 422
	virtual void function_423();  // 423
	virtual void function_424();  // 424
	virtual void function_425();  // 425
public:
	virtual void setGamemode(__int32);//426

public:
	float getBlocksPerTick() {
		Vec3 targetPos = *this->getPos();
		Vec3 targetPosOld = *this->getPosOld();
		float hVel = sqrtf(static_cast<float>(
			(pow((targetPos.x - targetPosOld.x), 2))
			+ (pow((targetPos.y - targetPosOld.y), 2))
			+ (pow((targetPos.z - targetPosOld.z), 2))));
		return hVel;
	}
	float getBlocksPerSecond();
	bool checkNameTagFunc();

	uintptr_t** vTable() {
		return reinterpret_cast<uintptr_t**>((uintptr_t*)(this) + 0x0);
	}
	GameMode* Getgamemode() {
		return *reinterpret_cast<GameMode**>((uintptr_t*)(this) + 0x1724);
	}
	class Level* getlevel() {
		return *reinterpret_cast<class Level**>(reinterpret_cast<__int32>(this) + 0x334);
	}
};
#pragma pack(pop)
class Player :public Entity {
public:
	C_PlayerInventoryProxy* getSupplies();
};
class LocalPlayer :public Player {
};
