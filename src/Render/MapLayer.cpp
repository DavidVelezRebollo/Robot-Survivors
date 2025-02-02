#include <Render/MapLayer.h>

void MapLayer::setTile(std::int32_t tileX, std::int32_t tileY, tmx::TileLayer::Tile tile, bool refresh)
{
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    selectedChunk->setTile(chunkLocale.x, chunkLocale.y, tile, refresh);
}

tmx::TileLayer::Tile MapLayer::getTile(std::int32_t tileX, std::int32_t tileY)
{
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    return selectedChunk->getTile(chunkLocale.x, chunkLocale.y);
}

void MapLayer::setColor(std::int32_t tileX, std::int32_t tileY, sf::Color color, bool refresh)
{
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    selectedChunk->setColor(chunkLocale.x, chunkLocale.y, color, refresh);
}

sf::Color MapLayer::getColor(std::int32_t tileX, std::int32_t tileY)
{
    sf::Vector2u chunkLocale;
    const auto& selectedChunk = getChunkAndTransform(tileX, tileY, chunkLocale);
    return selectedChunk->getColor(chunkLocale.x, chunkLocale.y);
}

void MapLayer::update(sf::Time elapsed)
{
    for (auto& c : m_visibleChunks)
    {
        for (AnimationState& as : c->getActiveAnimations())
        {
            as.currentTime += elapsed;

            tmx::TileLayer::Tile tile;
            std::int32_t animTime = 0;
            auto x = as.animTile.animation.frames.begin();
            while (animTime < as.currentTime.asMilliseconds())
            {
                if (x == as.animTile.animation.frames.end())
                {
                    x = as.animTile.animation.frames.begin();
                    as.currentTime -= sf::milliseconds(animTime);
                    animTime = 0;
                }

                tile.ID = x->tileID;
                animTime += x->duration;
                x++;
            }

            setTile(as.tileCords.x, as.tileCords.y, tile);
        }
    }
}
