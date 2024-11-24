#pragma once

#include <deque>
#include <string>

static std::deque<std::string> tea {
                                   "Чай Лунцзин",
                                   "Эрл Грей",
                                   "Сенча",
                                   "Пуэр",
                                   "Дарджилинг",
                                   "Ассам",
                                   "Матча",
                                   "Ганпаудер",
                                   "Оолонг",
                                   "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};

struct Model {
    using Deque = std::deque<std::string>;
    Deque items;
    Deque::iterator iterator = items.begin();
};
