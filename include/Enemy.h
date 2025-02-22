#pragma once
#include "GameObject.hpp"
#include "Projectile.h"


namespace PlanetDefenders
{
    class Enemy : public GameObject
    {

        sf::Clock shootClock;

        // that determine the scale, damage, speed shoot interval of the enemy
        float attribute;
        float projectileScale;
        float projectileDamage;
        float projectileSpeed;
        sf::Time shootInterval;

    protected:
        float hp;
    public:
        Enemy(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos,
            float attribute = 1.0f, float hp = 2.3f) :
            GameObject(
                texture,
                rect,
                pos,
                sf::Vector2f(0, 0.0f),
                0.0f
            ), projectileScale(1), projectileDamage(1), projectileSpeed(5), attribute(attribute)
        {
            getSprite().scale(attribute, attribute);
            setSpeed(4 / attribute);                     // big attribute, small speed
            setProjectileDamage(attribute * 1);          // big attribute, big damage
            setProjectileSpeed(6 / attribute);           // big attribute, small proj spd
            setProjectileScale(attribute * 1.1f);        // big attribute, big proj size
            // bass interval + (attribute*10)^2
            setShootInterval(EnemyShootEachProjInterval + sf::milliseconds(pow((attribute * 10), 2)));
            this->hp = hp * (attribute);                   // big attribute, small hp
        }
        ~Enemy();
        //sf::Vector2f getPosition
        //bool isOutOfBound() { return false; }
        bool isDead() { return hp <= 0; }
        bool isAlive() { return hp > 0; }

        void takeDamage(float x) { hp -= x; }

        float getHp() { return hp; }
        float getAttribute(){ return attribute; }
        void setHp(float x) { this->hp = x; }

        void setProjectileScale(float s) { projectileScale = s; }
        void setProjectileDamage(float s) { projectileDamage = s; }
        void setProjectileSpeed(float s) { projectileSpeed = s; }
        void setShootInterval(unsigned int ms) { shootInterval = sf::milliseconds(ms); }
        void setShootInterval(sf::Time t) { shootInterval = t; }

        Projectile* shoot();

        friend std::ostream& operator<<(std::ostream& output, Enemy& p)
        {
            output << "Enemy at" << " (" << p.getSprite().getPosition().x << ", "
                << p.getSprite().getPosition().y << ") "
                << "Attr: " << p.attribute << " "
                << "Hp: " << p.getHp();
            return output;
        }
    };
}

