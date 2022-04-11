package ru.second.annotationConfig;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

@Component
public @Data
class Tent implements Portable {
    @Value("${tent.humanCapacity}")
    private int humanCapacity;

    @PostConstruct
    public void init() {
        System.out.println("Создание бина палатки.");
    }

    @Override
    public void showInfo() {
        System.out.println("Название объекта: палатка");
        System.out.println("Вместимость палатки: " + this.humanCapacity + " человека");
    }

    @PreDestroy
    public void destroy() {
        System.out.println("Бин палатки уничтожен");
    }
}
