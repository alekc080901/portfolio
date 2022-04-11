# Вариант 20

excel_table <- read.csv("var20.csv")
data <- excel_table$x

selection_1 <- head(data, 10)
selection_2 <- head(data, 50)
selection_3 <- data

# Задание 2
f1 <- function(sel) {
    n <- length(sel)
    
    # Среднее выборочное
    print(sample_mean <- mean(sum(sel)) / n)
    
    # Несмещенная выборочная дисперсия
    print(variance_1 <- var(sel))
    
    # Смещенная выборочная дисперсия
    print(variance_2 <- variance_1 * (n - 1) / n)
    
    # Выборачная квантиль
    print(quan <- quantile(sel))
    
    # Оценки параметров нормального распределения
    print(a <- mean(sel))
    print(dev <- sd(sel))
    
    # Гистограмма
    hist(sel, main = "Гистограмма нормального распределения",
         freq = FALSE, xlab = "x", ylab = "h",  col = "chartreuse")
    
    curve(dnorm(x,
                mean = a,
                sd = dev),
          col = "red", lwd = 3,
          add = TRUE)
    
    # Функция распределения
    gauss_func <- ecdf(sel)
    
    plot(gauss_func,
         main = "Функция нормального распределения",
         xlab = "X", ylab = "P(X)")
    
    curve(pnorm(x,
                mean = a,
                sd = dev),
          col = "red", lwd = 3,
          add = TRUE)
    
    # Доверительный интервал мат. ожидания
    a1 = a - qt(p = 0.975, df = n - 1) * sqrt(dev) / sqrt(n)
    a2 = a + qt(p = 0.975, df = n - 1) * sqrt(dev) / sqrt(n)
    
    print(paste(a1, "< a <", a2))
    
    # Доверительный интервал дисперсии
    var1 = (n - 1) * variance_1 / qchisq(p = 0.975, df = n - 1)
    var2 = (n - 1) * variance_1 / qchisq(p = 0.025, df = n - 1)
    
    print(paste(var1, "< var <", var2))
    
    # График изменения интервала мат. ожидания
    conf_levels = seq(0.9, 0.9999999999, length.out = 1000)
    
    a_change_1 = a - qt(p = (conf_levels), df = n - 1) * dev / sqrt(n)
    a_change_2 = a + qt(p = (conf_levels), df = n - 1) * dev / sqrt(n)
    
    delta = a_change_2 - a_change_1
    
    plot(x = conf_levels, y = delta,
         type = "o",
         main = "Изменение длины интервалов мат. ожидания и дисперсии",
         
         xlab = "Значение уровня доверия", ylab = "Длина интервала",
         col = "chartreuse3")
    
    abline(v = 1.00,
        lty = 5, col = "red", lwd = 2)
    
    # График изменения интервала дисперсии
    var_change_1 = (n - 1) * variance_1 / qchisq(p = conf_levels, df = n - 1)
    var_change_2 = (n - 1) * variance_1 / qchisq(p = 1 - conf_levels, df = n - 1)
    
    delta = var_change_2 - var_change_1
    
    lines(x = conf_levels, y = delta,
         type = "o",
         col = "blue3")
    
    legend("topleft", c("Мат. ожидание", "Дисперсия"),
           fill = c("chartreuse3", "blue3"))
    
    abline(v = 1.00,
           lty = 5, col = "red", lwd = 2)
}

f1(selection_1)
f1(selection_2)
f1(selection_3)