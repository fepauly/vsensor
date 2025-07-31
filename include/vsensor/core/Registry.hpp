#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

namespace vsensor {
    template <typename FactoryT>
    class Registry {
        public:
            static Registry& instance() {
                static Registry inst;
                return inst;
            }

            void register_factory(std::string name, std::unique_ptr<FactoryT> factory) {
                m_map.emplace(std::move(name), std::move(factory));
            }

            FactoryT* get(const std::string& name) const noexcept {
                auto it = m_map.find(name);
                return it == m_map.end() ? nullptr : it->second.get();
            }

        private:
            std::unordered_map<std::string, std::unique_ptr<FactoryT>> m_map;
            Registry() = default;      
    };
}