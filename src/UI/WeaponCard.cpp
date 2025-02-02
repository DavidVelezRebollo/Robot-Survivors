#include <UI/WeaponCard.h>

void WeaponCard::updateCard(Weapon* weapon, int level)
{
	m_weaponText.setString(weapon->getName());
	m_weaponText.setOrigin(m_weaponText.getLocalBounds().width / 2.0f, m_weaponText.getLocalBounds().height / 2.0f);

	m_weaponLevelText.setString("Nivel " + std::to_string(level));
	m_weaponLevelText.setOrigin(m_weaponLevelText.getLocalBounds().width / 2.0f, m_weaponLevelText.getLocalBounds().height / 2.0f);

	sf::Texture& tex = *weapon->getSprite();
	m_weaponSprite.setTexture(tex, true);
	m_weaponSprite.setOrigin(m_weaponSprite.getLocalBounds().width / 2.0f, m_weaponSprite.getLocalBounds().height / 2.0f);

	float dmg = weapon->getLevelDamage(level);
	float cooldown = weapon->getLevelShootCooldown(level);

	m_weaponStats.setString("Daño: " + floatToString(dmg) + "\n\n\nCadencia de disparo: " + floatToString(cooldown));
	m_weaponStats.setOrigin(m_weaponStats.getLocalBounds().width / 2.0f, m_weaponStats.getLocalBounds().height / 2.0f);
}

void WeaponCard::setupCard(float xPos, float yPos)
{
	m_font.loadFromFile("../Data/NotJamUI15.ttf");

	m_background.setSize(sf::Vector2f(400.f, 500.f));
	m_background.setOrigin(sf::Vector2f{ m_background.getLocalBounds().width / 2.0f, m_background.getLocalBounds().height / 2.0f });
	m_background.setFillColor(sf::Color(49, 40, 45, 200));
	m_background.setOutlineThickness(3.f);
	m_background.setOutlineColor(sf::Color(60, 17, 45));
	m_background.setPosition(xPos, yPos);

	m_weaponText.setFont(m_font);
	m_weaponText.setFillColor(sf::Color(220, 190, 194));
	m_weaponText.setPosition(sf::Vector2f{ xPos, yPos / 2.0f + 50 });
	m_weaponText.setCharacterSize(25);

	m_weaponSprite.setPosition(xPos, yPos / 2.0f + 150.f);
	m_weaponSprite.setScale(4.f, 4.f);

	m_weaponLevelText.setFont(m_font);
	m_weaponLevelText.setFillColor(sf::Color(156, 186, 33));
	m_weaponLevelText.setPosition(xPos, yPos - 50.f);
	m_weaponLevelText.setCharacterSize(25);

	m_weaponStats.setFont(m_font);
	m_weaponStats.setFillColor(sf::Color(220, 190, 194));
	m_weaponStats.setPosition(sf::Vector2f{ xPos, yPos / 2.0f + 350.f });
	m_weaponStats.setCharacterSize(20);
}

void WeaponCard::render(sf::RenderWindow& window)
{
	window.draw(m_background);
	window.draw(m_weaponText);
	window.draw(m_weaponSprite);
	window.draw(m_weaponLevelText);
	window.draw(m_weaponStats);
}

std::string WeaponCard::floatToString(float value)
{
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(2) << value;

	return stream.str();
}
