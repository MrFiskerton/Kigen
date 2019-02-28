//
// Created by Roman Fiskov (roman.fiskov@gmail.com) [Mr.Fiskerton] on 19.07.18.
//

#include <Kigen/conversion/to_string.hpp>

namespace conversion {
    namespace {
        template<typename T>
        struct Type {
            typedef T type;
        };

        template<typename T>
        class BidirectionalMap { // Bidirectional  T <-> std::string
            static_assert(!std::is_same<T, std::string>::value, "Type different from std::string expected");
        public:
            explicit BidirectionalMap(std::size_t valueCount, std::size_t specialValueCount = 0)
                    : m_string_vector(valueCount + specialValueCount), m_T_map(),
                      m_specialValueCount(specialValueCount) {
            }

            void insert(T t, const std::string &str) {
                m_string_vector[t + m_specialValueCount] = str;
                m_T_map[str] = t;
            }

            const std::string &at(T t) const {
                auto index = static_cast<std::size_t>(t + m_specialValueCount);
                assertion(index < m_string_vector.size() + m_specialValueCount, "No match for key / mouse button found");
                return m_string_vector[index];
            }

            T at(const std::string &string) const {
                auto it = m_T_map.find(string);
                assertion(it != m_T_map.end(), "No match for string found");
                return it->second;
            }

        private:
            std::vector<std::string> m_string_vector;
            std::map<std::string, T> m_T_map;
            std::size_t m_specialValueCount;
        };

        BidirectionalMap<sf::Keyboard::Key> init(Type<sf::Keyboard::Key>) {
            BidirectionalMap<sf::Keyboard::Key> bimap(sf::Keyboard::KeyCount, 1);

#define     INSERT_MAPPING(identifier) bimap.insert(sf::Keyboard::identifier, #identifier)

            INSERT_MAPPING(Unknown);
            INSERT_MAPPING(A);
            INSERT_MAPPING(B);
            INSERT_MAPPING(C);
            INSERT_MAPPING(D);
            INSERT_MAPPING(E);
            INSERT_MAPPING(F);
            INSERT_MAPPING(G);
            INSERT_MAPPING(H);
            INSERT_MAPPING(I);
            INSERT_MAPPING(J);
            INSERT_MAPPING(K);
            INSERT_MAPPING(L);
            INSERT_MAPPING(M);
            INSERT_MAPPING(N);
            INSERT_MAPPING(O);
            INSERT_MAPPING(P);
            INSERT_MAPPING(Q);
            INSERT_MAPPING(R);
            INSERT_MAPPING(S);
            INSERT_MAPPING(T);
            INSERT_MAPPING(U);
            INSERT_MAPPING(V);
            INSERT_MAPPING(W);
            INSERT_MAPPING(X);
            INSERT_MAPPING(Y);
            INSERT_MAPPING(Z);
            INSERT_MAPPING(Num0);
            INSERT_MAPPING(Num1);
            INSERT_MAPPING(Num2);
            INSERT_MAPPING(Num3);
            INSERT_MAPPING(Num4);
            INSERT_MAPPING(Num5);
            INSERT_MAPPING(Num6);
            INSERT_MAPPING(Num7);
            INSERT_MAPPING(Num8);
            INSERT_MAPPING(Num9);
            INSERT_MAPPING(Escape);
            INSERT_MAPPING(LControl);
            INSERT_MAPPING(LShift);
            INSERT_MAPPING(LAlt);
            INSERT_MAPPING(LSystem);
            INSERT_MAPPING(RControl);
            INSERT_MAPPING(RShift);
            INSERT_MAPPING(RAlt);
            INSERT_MAPPING(RSystem);
            INSERT_MAPPING(Menu);
            INSERT_MAPPING(LBracket);
            INSERT_MAPPING(RBracket);
            INSERT_MAPPING(SemiColon);
            INSERT_MAPPING(Comma);
            INSERT_MAPPING(Period);
            INSERT_MAPPING(Quote);
            INSERT_MAPPING(Slash);
            INSERT_MAPPING(BackSlash);
            INSERT_MAPPING(Tilde);
            INSERT_MAPPING(Equal);
            INSERT_MAPPING(Dash);
            INSERT_MAPPING(Space);
            INSERT_MAPPING(Return);
            INSERT_MAPPING(BackSpace);
            INSERT_MAPPING(Tab);
            INSERT_MAPPING(PageUp);
            INSERT_MAPPING(PageDown);
            INSERT_MAPPING(End);
            INSERT_MAPPING(Home);
            INSERT_MAPPING(Insert);
            INSERT_MAPPING(Delete);
            INSERT_MAPPING(Add);
            INSERT_MAPPING(Subtract);
            INSERT_MAPPING(Multiply);
            INSERT_MAPPING(Divide);
            INSERT_MAPPING(Left);
            INSERT_MAPPING(Right);
            INSERT_MAPPING(Up);
            INSERT_MAPPING(Down);
            INSERT_MAPPING(Numpad0);
            INSERT_MAPPING(Numpad1);
            INSERT_MAPPING(Numpad2);
            INSERT_MAPPING(Numpad3);
            INSERT_MAPPING(Numpad4);
            INSERT_MAPPING(Numpad5);
            INSERT_MAPPING(Numpad6);
            INSERT_MAPPING(Numpad7);
            INSERT_MAPPING(Numpad8);
            INSERT_MAPPING(Numpad9);
            INSERT_MAPPING(F1);
            INSERT_MAPPING(F2);
            INSERT_MAPPING(F3);
            INSERT_MAPPING(F4);
            INSERT_MAPPING(F5);
            INSERT_MAPPING(F6);
            INSERT_MAPPING(F7);
            INSERT_MAPPING(F8);
            INSERT_MAPPING(F9);
            INSERT_MAPPING(F10);
            INSERT_MAPPING(F11);
            INSERT_MAPPING(F12);
            INSERT_MAPPING(F13);
            INSERT_MAPPING(F14);
            INSERT_MAPPING(F15);
            INSERT_MAPPING(Pause);

            assertion(sf::Keyboard::KeyCount == 101, "Number of SFML keys has changed");
#undef      INSERT_MAPPING
            return bimap;
        }

        BidirectionalMap<sf::Mouse::Button> init(Type<sf::Mouse::Button>) {
            BidirectionalMap<sf::Mouse::Button> bimap(sf::Mouse::ButtonCount);

#define     INSERT_MAPPING(identifier) bimap.insert(sf::Mouse::identifier, #identifier)

            INSERT_MAPPING(Left);
            INSERT_MAPPING(Right);
            INSERT_MAPPING(Middle);
            INSERT_MAPPING(XButton1);
            INSERT_MAPPING(XButton2);

            assertion(sf::Mouse::ButtonCount == 5, "Number of SFML mouse buttons has changed");
#undef      INSERT_MAPPING
            return bimap;
        }

        BidirectionalMap<sf::Joystick::Axis> init(Type<sf::Joystick::Axis>) {
            BidirectionalMap<sf::Joystick::Axis> bimap(sf::Joystick::AxisCount);

#define     INSERT_MAPPING(identifier) bimap.insert(sf::Joystick::identifier, #identifier)

            INSERT_MAPPING(X);
            INSERT_MAPPING(Y);
            INSERT_MAPPING(Z);
            INSERT_MAPPING(R);
            INSERT_MAPPING(U);
            INSERT_MAPPING(V);
            INSERT_MAPPING(PovX);
            INSERT_MAPPING(PovY);

            assertion(sf::Joystick::AxisCount == 8, "Number of SFML joystick axes has changed");
#undef      INSERT_MAPPING
            return bimap;
        }

        BidirectionalMap<sf::Event::EventType> init(Type<sf::Event::EventType>) {
            BidirectionalMap<sf::Event::EventType> bimap(sf::Event::Count);

#define     INSERT_MAPPING(identifier) bimap.insert(sf::Event::EventType::identifier, #identifier)

            INSERT_MAPPING(Closed);
            INSERT_MAPPING(Resized);
            INSERT_MAPPING(LostFocus);
            INSERT_MAPPING(GainedFocus);
            INSERT_MAPPING(TextEntered);
            INSERT_MAPPING(KeyPressed);
            INSERT_MAPPING(KeyReleased);
            INSERT_MAPPING(MouseWheelMoved);
            INSERT_MAPPING(MouseWheelScrolled);
            INSERT_MAPPING(MouseButtonPressed);
            INSERT_MAPPING(MouseButtonReleased);
            INSERT_MAPPING(MouseMoved);
            INSERT_MAPPING(MouseEntered);
            INSERT_MAPPING(MouseLeft);
            INSERT_MAPPING(JoystickButtonPressed);
            INSERT_MAPPING(JoystickButtonReleased);
            INSERT_MAPPING(JoystickMoved);
            INSERT_MAPPING(JoystickConnected);
            INSERT_MAPPING(JoystickDisconnected);
            INSERT_MAPPING(TouchBegan);
            INSERT_MAPPING(TouchMoved);
            INSERT_MAPPING(TouchEnded);
            INSERT_MAPPING(SensorChanged);

            assertion(sf::Event::Count == 23 , "Number of SFML Event type has changed");
#undef      INSERT_MAPPING
            return bimap;
        }

        template<typename T>
        BidirectionalMap<T> &instance() {
            static BidirectionalMap<T> instance = init(Type<T>());
            return instance;
        }

    } // namespace

    std::string to_string(sf::Keyboard::Key key) {
        return instance<sf::Keyboard::Key>().at(key);
    }

    std::string to_string(sf::Mouse::Button button) {
        return instance<sf::Mouse::Button>().at(button);
    }

    std::string to_string(sf::Joystick::Axis axis) {
        return instance<sf::Joystick::Axis>().at(axis);
    }

    std::string to_string(sf::Event::EventType event_type) {
        return instance<sf::Event::EventType>().at(event_type);
    }

    sf::Keyboard::Key to_KeyboardKey(const std::string &string) {
        return instance<sf::Keyboard::Key>().at(string);
    }

    sf::Mouse::Button to_MouseButton(const std::string &string) {
        return instance<sf::Mouse::Button>().at(string);
    }

    sf::Joystick::Axis to_JoystickAxis(const std::string &string) {
        return instance<sf::Joystick::Axis>().at(string);
    }

    sf::Event::EventType to_EventType(const std::string &string) {
        return instance<sf::Event::EventType>().at(string);
    }
} // namespace conversion