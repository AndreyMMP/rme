//////////////////////////////////////////////////////////////////////
// This file is part of Remere's Map Editor
//////////////////////////////////////////////////////////////////////
// Remere's Map Editor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Remere's Map Editor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#ifndef RME_SPAWN_H_
#define RME_SPAWN_H_

#include <string>
#include <vector>

class Tile;

struct SpawnMonsterEntry {
	std::string name;
	uint16_t chance;
};

struct SpawnMonsterPool {
	int32_t offsetX;
	int32_t offsetY;
	uint16_t z;
	int32_t spawntime;
	std::vector<SpawnMonsterEntry> monsters;
};

class Spawn
{
public:
	Spawn(int size = 3);

	Spawn* deepCopy() const;

	bool isSelected() const noexcept { return selected; }
	void select() noexcept { selected = true; }
	void deselect() noexcept { selected = false; }

	int getSize() const noexcept { return size; }
	void setSize(int newsize) {
		ASSERT(size < 100);
		size = newsize;
	}

	const std::vector<SpawnMonsterPool>& getMonsterPools() const noexcept { return monsterPools; }
	void addMonsterPool(const SpawnMonsterPool& pool) { monsterPools.push_back(pool); }
	bool hasMonsterPoolAt(int32_t offsetX, int32_t offsetY) const;

	// Does not compare selection!
	bool operator==(const Spawn& other) { return size == other.size; }
	bool operator!=(const Spawn& other) { return size != other.size; }

protected:
	int size;
	bool selected;
	std::vector<SpawnMonsterPool> monsterPools;
};

typedef std::set<Position> SpawnPositionList;
typedef std::list<Spawn*> SpawnList;

class Spawns
{
public:
	void addSpawn(Tile* tile);
	void removeSpawn(Tile* tile);

	SpawnPositionList::iterator begin() noexcept { return spawns.begin(); }
	SpawnPositionList::const_iterator begin() const noexcept { return spawns.begin(); }
	SpawnPositionList::iterator end() noexcept { return spawns.end(); }
	SpawnPositionList::const_iterator end() const noexcept { return spawns.end(); }
	void erase(SpawnPositionList::iterator iter) noexcept { spawns.erase(iter); }
	SpawnPositionList::iterator find(Position& pos) { return spawns.find(pos); }

private:
	SpawnPositionList spawns;
};

#endif
