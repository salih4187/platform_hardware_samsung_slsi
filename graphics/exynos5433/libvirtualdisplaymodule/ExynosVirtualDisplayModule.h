#ifndef EXYNOS_VIRTUAL_DISPLAY_MODULE_H
#define EXYNOS_VIRTUAL_DISPLAY_MODULE_H

#include "ExynosVirtualDisplay.h"

class ExynosVirtualDisplayModule : public ExynosVirtualDisplay {
    public:
        ExynosVirtualDisplayModule(struct exynos5_hwc_composer_device_1_t *pdev);
        ~ExynosVirtualDisplayModule();

        void init(hwc_display_contents_1_t __unused *virtual_contents);

        void setPriContents(hwc_display_contents_1_t __unused *contents);

        virtual int32_t getDisplayAttributes(const uint32_t attribute, uint32_t config);
};

#endif
