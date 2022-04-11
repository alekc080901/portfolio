# ЧАСТЬ 1

# Считываем данные под 20 вариант
all_info <- read.csv("bmw.csv", row.names = NULL)
info_table <- table(year = all_info$year[all_info$model == " X1"],
              fuel = all_info$fuelType[all_info$model == " X1"])

a <- 0.001
info_table

# Убираем нулевые строки
all_info_corr <- all_info
all_info_corr$year_united <- all_info_corr$year
all_info_corr$year_united[all_info_corr$year %in% 2010:2016] <- '2010-2016'

info_table <- table(year = all_info_corr$fuelType[all_info_corr$model == " X1"],
                    fuel = all_info_corr$year_united[all_info_corr$model == " X1"])

info_table

# Проверяем гипотезу независимости признаков
test_result <- chisq.test(info_table)
h <- test_result$statistic

print(h_cr <- qchisq(1 - a,
                     df = (nrow(info_table) - 1) * (ncol(info_table) - 1)))

print(paste(h, ifelse(h <= h_cr, "<=", ">"), h_cr))

# ЧАСТЬ 2

library(corrplot)

# Исходная модель с числовыми столбцами
data <- all_info[, sapply(all_info[all_info$model == " X1",], is.numeric)]

# Таблица корреляций
Mcor <- cor(data)
Mcor
corrplot(Mcor, method = "color", addCoef.col = "darkred", number.digits = 1,
         number.cex = 1.3)

# Обычная модель
model1 <- lm(price~year  + mileage + tax + mpg + engineSize, data)
# price = 2055*year - 0.1275*mileage + 3.043*tax + 21.64*mpg + 10080 * engineSize - 4143000

# Коррелирующая модель
model2 <- lm(price~year + tax + mpg + engineSize, data)
# price = 3102*year + 11.77*tax + 18.67*mpg + 9724 * engineSize - 6257000

summary(model1)
summary(model2)

# Создание и вывод Q-Q графика 1 модели
e <- residuals(model1)
qqnorm(e, pch = 16, cex = 0.5)
qqline(e, lty = 2, col = "red")

# Создание и вывод Q-Q графика 2 модели
r <- residuals(model2)
qqnorm(r, pch = 16, cex = 0.5)
qqline(r, lty = 2, col = "red")

# Прогнозирование
data_new <- data.frame(year = 2025, mileage = 20000, tax = 125, mpg = 50,
                       engineSize = 3) 
price_new <- predict(model1, data_new)
price_new

# Прогнозирование
data_new <- data.frame(year = 2025, tax = 125, mpg = 50,
                       engineSize = 3) 
price_new <- predict(model2, data_new)
price_new
