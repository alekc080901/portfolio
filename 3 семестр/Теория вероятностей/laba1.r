# целочисленный вектор, значение которого - номер измерения
num <- 1:15
num_str <- paste0("X", as.character(num))

# вектор с вещественными компонентами - значениями исследуемой характеристики
a_6 <- c(2.79,
         2.52,
         2.38,
         3.38,
         3.12,
         3.32,
         3.13,
         3.06,
         1.59,
         2.26,
         2.94,
         2.27,
         2.8,
         2.86,
         2.62)

a_6_8 <-
    c(1.15,
      2.24,
      2.34,
      2.06,
      1.31,
      1.98,
      2.17,
      2.73,
      2.13,
      1.73,
      2.1,
      2.41,
      2.26,
      1.31,
      2.17)

a_8 <-
    c(1.72,
      1.85,
      2.03,
      1.46,
      1.9,
      1.85,
      2.3,
      2.27,
      1.94,
      1.64,
      2.49,
      1.74,
      2.87,
      1.15,
      2.76)

# вектор, компоненты которого - строки - значения факторной переменной
b <- ceiling(a_6 + a_6_8 + a_8)

b <- ifelse(b <= 6, "низкая",
            ifelse(b == 7, "средняя", "высокая"))

# фактор, полученный преобразованием текстового вектора b
b_factor <- ordered(b, c("низкая", "средняя", "высокая"))

# вывод
num_str
a_6
a_6_8
a_8
b
b_factor



# создание таблицы
my_frame <- data.frame(
    шесть  = a_6,
    шесть_восемь  = a_6_8,
    восемь  = a_8,
    заболеваемость  = b_factor,
    row.names = num_str
)

# Содержимое
my_frame

# Размерность
paste(ncol(my_frame), "X", nrow(my_frame))

# Структура
str(my_frame)

# Названия признаков
colnames(my_frame)

# Первые четыре строки
head(my_frame, 4)

# Диапазон
my_frame$шесть[my_frame$шесть  < 3 & my_frame$шесть  > 2]

# Фактор
my_frame[my_frame$заболеваемость  <= "средняя", ]

my_frame[1, ]
my_frame[3, ]
my_frame[6, ]
my_frame[9, ]
my_frame[10, ]

# Минимальное значение таблицы
min(c(my_frame$шесть, my_frame$шесть_восемь, my_frame$восемь))



# Добавление 3 строк
my_frame <- rbind(
    my_frame,
    data.frame(
        шесть  = c(2.63, 3.15, 2.08),
        шесть_восемь  = c(2.02, 2.64, 1.75),
        восемь  = c(1.73, 2.06, 1.45),
        заболеваемость  = c("средняя", "высокая", "низкая"),
    )
)

# Средние значения и запись в файл
(my_frame_mean <-
        mean(c(
            my_frame$шесть, my_frame$шесть_восемь, my_frame$восемь
        )))

(my_frame_sd <-
        sd(c(
            my_frame$шесть, my_frame$шесть_восемь, my_frame$восемь
        )))

writeLines(paste(my_frame_mean, my_frame_sd), "laba.txt")

# Добавление вектора New
new_1 <-
    apply(my_frame[, c("шесть", "шесть_восемь", "восемь")], 1, mean)
new_2 <-
    apply(my_frame[, c("шесть", "шесть_восемь", "восемь")], 1, sd)

new <- paste(as.vector(new_1), as.vector(new_2), sep = "; ")

cbind(my_frame, data.frame(
    New = new,
    row.names = c(num_str, "X16", "X17", "Xrnorm
))



# Чтение из excel
library("xlsx")

flat <- read.xlsx("Flat98.xlsx", sheetIndex = 1)

# Вывод первых 5 строк
writehead(flat, 5)

# Функция
mode <- function(x) {
    ux <- unique(x)
    ux[which.max(tabulate(match(x, ux)))]
}

f <- function(v) {
    if (length(v) < 4) {
        print("Длина должна быть больше или равна 4!")
        return
    }
    
    m <- mode(v)
    
    v <- v[v != m]
    result <- vector()
    for (i in 1:4) {
        dif <- abs(v - m)
        min_dif_pos <- which.min(dif)
        result <- c(result, v[min_dif_pos])
        v <- v[-min_dif_pos]
    }
    result
}

# Произвольные данные
f(c(4, 5, 3, 3, 3, 4, 2, 5, 6, 6))

# Данные из Excel
f(flat$price)
f(flat$kitsp)