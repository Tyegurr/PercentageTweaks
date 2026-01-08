#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

//uhh
class $modify(PlayLayerHook, PlayLayer) {
    struct Fields {
        int m_percentagePrecision;
        bool m_scientificNotation;
    };
    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();

        if (m_isPlatformer == true) return; // don't even bother
        
        Fields* fields = m_fields.self();

        fields->m_percentagePrecision = Mod::get()->getSettingValue<int>("percentage-precision");
        fields->m_scientificNotation = Mod::get()->getSettingValue<bool>("scientific-notation");
    }
    void updateProgressbar() {
        PlayLayer::updateProgressbar();

        if (m_player1 == nullptr) return;
        if (m_isPlatformer == true) return;

        Fields* fields = m_fields.self();

        // percentage calculators happen here
        cocos2d::CCPoint realPlayerPosition = m_player1->getRealPosition();
        long double longPercentage = (static_cast<long double>(realPlayerPosition.x) / static_cast<long double>(m_endXPosition)) * 100.0L;
        // now we can set the percentage label text
        if (fields->m_scientificNotation == true) {
            m_percentageLabel->setString(fmt::format("{:.{}e}%", longPercentage, fields->m_percentagePrecision).c_str());
        } else {
            m_percentageLabel->setString(fmt::format("{:.{}f}%", longPercentage, fields->m_percentagePrecision).c_str());
        }
    }
};