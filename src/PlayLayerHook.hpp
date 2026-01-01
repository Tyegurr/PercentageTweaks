#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayerHook, PlayLayer) {
    struct Fields {
        long double m_longPercentage;
        int m_percentagePrecision;
        bool m_scientificNotation;
    };
    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();

        m_fields->m_percentagePrecision = Mod::get()->getSettingValue<int>("percentage-precision");
        m_fields->m_scientificNotation = Mod::get()->getSettingValue<bool>("scientific-notation");

        // setting up percentage label
        m_percentageLabel->setAnchorPoint({0.5, 1.0});
        m_percentageLabel->setPositionY(m_percentageLabel->getPositionY() + 8.0f);
        m_percentageLabel->setScale(Mod::get()->getSettingValue<float>("percentage-label-scale"));
    }
    void updateProgressbar() {
        PlayLayer::updateProgressbar();

        if (m_player1 == nullptr) return;

        // percentage calculators happen here
        cocos2d::CCPoint realPlayerPosition = m_player1->getRealPosition();
        m_fields->m_longPercentage = (static_cast<long double>(realPlayerPosition.x) / static_cast<long double>(m_endXPosition)) * 100.0L;
        // now we can set the percentage label text
        if (m_fields->m_scientificNotation == true) {
            m_percentageLabel->setString(fmt::format("{:.{}e}%", m_fields->m_longPercentage, m_fields->m_percentagePrecision).c_str());
        } else {
            m_percentageLabel->setString(fmt::format("{:.{}f}%", m_fields->m_longPercentage, m_fields->m_percentagePrecision).c_str());
        }
    }
};