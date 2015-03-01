#include "AnimatedTex.hpp"
AnimatedTex::AnimatedTex(sf::Time frameTime, bool paused, bool looped) :
    m_animation(NULL), m_frameTime(frameTime), m_currentFrame(0), m_isPaused(paused), m_isLooped(looped), m_texture(NULL)
{
}
void AnimatedTex::setAnimation(const Animation& animation){
    m_animation = &animation;
    m_texture = m_animation->getSpriteSheet();
    m_currentFrame = 0;
    setFrame(m_currentFrame);
}
void AnimatedTex::setFrameTime(sf::Time time)
{
    m_frameTime = time;
}
void AnimatedTex::play(){
    m_isPaused = false;
}
void AnimatedTex::play(const Animation& animation){
    if (getAnimation() != &animation)
        setAnimation(animation);
    play();
}
void AnimatedTex::pause(){
    m_isPaused = true;
}
void AnimatedTex::stop(){
    m_isPaused = true;
    m_currentFrame = 0;
    setFrame(m_currentFrame);
}
void AnimatedTex::setLooped(bool looped){
    m_isLooped = looped;
}
void AnimatedTex::setColor(const sf::Color& color){
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    m_vertices[3].color = color;
}
const Animation* AnimatedTex::getAnimation() const{
    return m_animation;
}
bool AnimatedTex::isLooped() const
{
    return m_isLooped;
}
bool AnimatedTex::isPlaying() const{
    return !m_isPaused;
}
sf::Time AnimatedTex::getFrameTime() const{
    return m_frameTime;
}
void AnimatedTex::setFrame(std::size_t newFrame)
{
    if (m_animation){
        sf::IntRect rect = m_animation->getFrame(newFrame);
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
    //m_currentTime = sf::Time::Zero;
}
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
void AnimatedTex::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if (m_animation && m_texture){
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::Quads, states);
    }
}
