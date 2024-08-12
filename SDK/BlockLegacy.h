#pragma once
#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "../SDK/TextHolder.h"
class Material {



};
class Entity;
class	Block;
class BlockSource;
class BlockLegacy
{
};
class Block {

};
class CompoundTag;
class BlockActor {
private:
	virtual void destructor();
	virtual __int64 load(__int32&, CompoundTag*, __int32&);

public:
	virtual bool save(CompoundTag*);
};
class BlockSource {
public:
	virtual void Destructor();
	virtual Block* getBlock(int, int, int);
	virtual Block* getBlock(Vec3i const&);
	virtual Block* getBlock(Vec3i const&, int);
	virtual BlockActor* getBlockEntity(Vec3i const&);
	virtual Block* getExtraBlock(Vec3i const&);
	virtual Block* getLiquidBlock(Vec3i const&);
	virtual bool hasBlock(Vec3i const&);
	virtual bool containsMaterial(AABB const&, struct MaterialType);
	virtual Material* getMaterial(Vec3i const&);
	virtual Material* getMaterial(int, int, int);
	virtual bool hasChunksAt(struct Bounds const&);
	virtual bool hasChunksAt(Vec3i const&, int);
	virtual bool hasChunksAt(AABB const&);
	virtual int getDimensionId(void);
	virtual __int32 getWeakRef(void);
	virtual void addListener(struct BlockSourceListener&);
	virtual void removeListener(BlockSourceListener&);
	virtual class EntityList* fetchEntities(Entity const*, AABB const&, bool);
	virtual class EntityList* fetchEntities(__int64, AABB const&, Entity const*);
	virtual void setBlock(Vec3i const&, Block const&, int, class ActorBlockSyncMessage const*, Entity*);
	virtual bool containsAnyLiquid(AABB const&);
	virtual int getMinHeight(void);
	virtual class Dimension* getDimension(void);
	virtual class Dimension* getDimensionConst(void);
	virtual __int32 getILevel(void);
	virtual std::vector<AABB>* fetchAABBs(AABB const&, bool);
	virtual std::vector<AABB>* fetchCollisionShapes(AABB const&, float*, bool, class IActorMovementProxy*);
	virtual AABB* getTallestCollisionShape(AABB const&, float*, bool, IActorMovementProxy*);
	virtual __int32 getChunkSource(void);
	virtual bool isSolidBlockingBlock(Vec3i const&);
};

