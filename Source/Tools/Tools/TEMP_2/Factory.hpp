
#pragma once

namespace AOC::Tools
{
    template <typename ProductFamilyT>
    class Factory
    {
    protected:
        class Permit
        {
        public:
            Permit() = default;
        };

    public:
        template <typename ProductT>
        class Blueprint : public ProductFamilyT
        {
        public:
            static bool Register()
            {
                return false;
            }

        private:
            Blueprint()
                : ProductFamilyT(Permit{})
            {
                (void) sm_registered;
            }

            static bool sm_isRegistered;
        };

        Factory(Permit) = default;
    };

    template <typename ProductFamilyT>
    template <typename ProductT>
    bool Factory<ProductFamilyT>::Blueprint<ProductT>::sm_isRegistered =
        Factory<ProductFamilyT>::Blueprint<ProductT>::Register();
}