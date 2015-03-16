#include "AnimatedTex.hpp"
/**
 * \param frameTime - Czas wyświetlania klatki, paused - pauza
 * looped - zapętlenie
 */
AnimatedTex::AnimatedTex(sf::Time frameTime, bool paused, bool looped) :
    m_animation(NULL), m_frameTime(frameTime), m_currentFrame(0), m_isPaused(paused), m_isLooped(looped), m_texture(NULL)
{
}
/**
 * \brief Ustawia animacje
 * \param animation - animacja
 *
 */
void AnimatedTex::setAnimation(const Animation& animation){
    m_animation = &animation;
    m_texture = m_animation->getSpriteSheet();
    m_currentFrame = 0;
    setFrame(m_currentFrame);
}
/**
 * \brief Ustawia czas między klatkami
 * \param time - czas
 */
void AnimatedTex::setFrameTime(sf::Time time)
{
    m_frameTime = time;
}
/**
 * \brief Uruchamia animacje
 */
void AnimatedTex::play(){
    m_isPaused = false;
}
/**
 * \brief Ustawia animacje i ją uruchamia
 * \param animation - animacja
 */
void AnimatedTex::play(const Animation& animation){
    if (getAnimation() != &animation)
        setAnimation(animation);
    play();
}
/**
 * \brief Zatrzymuje animacje
 *
 */
void AnimatedTex::pause(){
    m_isPaused = true;
}
/**
 * \brief Zatrzymuje animacje i ustawia aktualną klatke na na pierwszą
 */
void AnimatedTex::stop(){
    m_isPaused = true;
    m_currentFrame = 0;
    setFrame(m_currentFrame);
}
/**
 * \brief Ustawia zapętlenie animacji
 * \param looped - zapętlenie
 */
void AnimatedTex::setLooped(bool looped){
    m_isLooped = looped;
}
/**
 * \brief Ustawia kolor teksturki klatki
 * \param color - kolor
 */
void AnimatedTex::setColor(const sf::Color& color){
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}
/**
 * \brief Zwraca wskaźnik na animacje
 * \return Animacja
 */
const Animation* AnimatedTex::getAnimation() const{
    return m_animation;
}
#include <iostream>
/**
 * \brief Zwraca zapętlenie animacji
 * \return Zapętlenie
 */
bool AnimatedTex::isLooped() const
{
    return m_isLooped;
}
/**
 * \brief Zwraca wartość czy animacja aktualnie jest odgrywana
 * \return Stan
 */
bool AnimatedTex::isPlaying() const{
    return !m_isPaused;
}
/**
 * \brief Zwraca czas między klatkami
 * \return sf::Time - czas
 */
sf::Time AnimatedTex::getFrameTime() const{
    return m_frameTime;
}
/**
 * \brief Ustawia klatke
 * \details Przełącza klatke
 * \param Numer klatki
 */
 #include <iostream>
 #include <stdexcept>
void AnimatedTex::setFrame(std::size_t newFrame){
    if (m_animation){
        sf::IntRect rect;
        try{
        rect = m_animation->getFrame(newFrame);
        }
        catch (const std::out_of_range& oor)
        {
        std::cout << "Out of Range error: " << oor.what() << '\n';
        }
        m_vertices[0].position = sf::Vector2f(0.f, 0.f);
        m_vertices[1].position = sf::Vector2f(0.f, static_cast<unsigned int>(rect.height));
        m_vertices[2].position = sf::Vector2f(static_cast<unsigned int>(rect.width), static_cast<unsigned int>(rect.height));
        m_vertices[3].position = sf::Vector2f(static_cast<unsigned int>(rect.width), 0.f);
        unsigned int left = rect.left;
        unsigned int right = left + rect.width;
        unsigned int top = rect.top;
        unsigned int bottom = top + rect.height;
        m_vertices[0].texCoords = sf::Vector2f(left,top);
        m_vertices[1].texCoords = sf::Vector2f(left,bottom);
        m_vertices[2].texCoords = sf::Vector2f(right,bottom);
        m_vertices[3].texCoords = sf::Vector2f(right,top);
    }
}
/**
 * \brief Odświeża animacje
 * \param deltaTime - delta
 * \details Przełącza klatki animacji
 */
void AnimatedTex::update(sf::Time deltaTime){
    if (!m_isPaused && m_animation){
        m_currentTime += deltaTime;
        if (m_currentTime >= m_frameTime){
            m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());
            if (m_currentFrame + 1 < m_animation->getSize())
                m_currentFrame++;
            else{
                m_currentFrame = 0;
                if (!m_isLooped){
                    m_isPaused = true;
                }
            }
            setFrame(m_currentFrame);
        }
    }
}
/**
 * \brief Rysuje animacje
 *
 */
void AnimatedTex::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if (m_animation && m_texture){
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::Quads, states);
    }
}
