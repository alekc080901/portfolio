package com.company;

import java.util.List;

abstract public class AbstractFactory {

    abstract public Answer createOptionAnswer(List<String> answerList);

    abstract public Answer createTextAnswer(String answerText);
}
