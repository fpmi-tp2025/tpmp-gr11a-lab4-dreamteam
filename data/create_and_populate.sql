-- Удаление старых таблиц (для повторного запуска)
DROP TABLE IF EXISTS APP_USERS;
DROP TABLE IF EXISTS DRIVERS;
DROP TABLE IF EXISTS CARS;
DROP TABLE IF EXISTS ORDERS;
DROP TABLE IF EXISTS EARNINGS;
DROP TABLE IF EXISTS APP_CONFIG;

-- -----------------------------------------------------
-- Таблица пользователей системы
-- -----------------------------------------------------
CREATE TABLE APP_USERS (
    UserID INTEGER PRIMARY KEY AUTOINCREMENT,
    Username TEXT NOT NULL UNIQUE,
    PasswordHash TEXT NOT NULL,
    Role TEXT NOT NULL CHECK (Role IN ('admin', 'dispatcher', 'driver')),
    CreatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- -----------------------------------------------------
-- Таблица водителей
-- -----------------------------------------------------
CREATE TABLE DRIVERS (
    DriverID INTEGER PRIMARY KEY AUTOINCREMENT,
    LastName TEXT NOT NULL,
    Category TEXT,
    Experience INTEGER,
    Address TEXT,
    BirthYear INTEGER CHECK (BirthYear BETWEEN 1950 AND 2005),
    LicenseNumber TEXT UNIQUE,
    HireDate DATE,
    Status TEXT DEFAULT 'active' CHECK (Status IN ('active', 'on_leave', 'terminated'))
);

-- -----------------------------------------------------
-- Таблица автомобилей
-- -----------------------------------------------------
CREATE TABLE CARS (
    CarID INTEGER PRIMARY KEY AUTOINCREMENT,
    LicensePlate TEXT NOT NULL UNIQUE,
    Make TEXT,
    Model TEXT,
    Year INTEGER,
    InitialMileage INTEGER DEFAULT 0,
    CurrentMileage INTEGER,
    LoadCapacity REAL,
    FuelType TEXT,
    Status TEXT DEFAULT 'available' CHECK (Status IN ('in_use', 'in_repair', 'available')),
    ImagePath TEXT
);

-- -----------------------------------------------------
-- Таблица заказов
-- -----------------------------------------------------
CREATE TABLE ORDERS (
    OrderID INTEGER PRIMARY KEY AUTOINCREMENT,
    OrderDate DATE NOT NULL,
    DriverID INTEGER,
    CarID INTEGER,
    StartLocation TEXT,
    EndLocation TEXT,
    Distance REAL,
    CargoWeight REAL,
    Price REAL,
    OrderStatus TEXT DEFAULT 'completed' CHECK (OrderStatus IN ('completed', 'in_progress', 'cancelled')),
    FOREIGN KEY (DriverID) REFERENCES DRIVERS(DriverID),
    FOREIGN KEY (CarID) REFERENCES CARS(CarID)
);

-- -----------------------------------------------------
-- Таблица начислений
-- -----------------------------------------------------
CREATE TABLE EARNINGS (
    EarningID INTEGER PRIMARY KEY AUTOINCREMENT,
    DriverID INTEGER,
    OrderID INTEGER,
    PeriodStart DATE,
    PeriodEnd DATE,
    TotalPrice REAL,
    DriverEarning REAL AS (TotalPrice * 0.20) STORED,
    FOREIGN KEY (DriverID) REFERENCES DRIVERS(DriverID),
    FOREIGN KEY (OrderID) REFERENCES ORDERS(OrderID)
);

-- -----------------------------------------------------
-- Конфигурационные параметры
-- -----------------------------------------------------
CREATE TABLE APP_CONFIG (
    ConfigKey TEXT PRIMARY KEY,
    ConfigValue TEXT,
    Description TEXT,
    UpdatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- -----------------------------------------------------
-- Добавление тестовых данных
-- -----------------------------------------------------

-- Пользователи
INSERT INTO APP_USERS (Username, PasswordHash, Role) VALUES
('admin', 'admin123', 'admin'),
('driver1', 'driver123', 'driver');

-- Водители
INSERT INTO DRIVERS (LastName, Category, Experience, Address, BirthYear, LicenseNumber, HireDate) VALUES
('Иванов', 'C', 5, 'ул. Ленина, 10', 1985, 'A123BC77', '2020-01-15'),
('Петров', 'B', 10, 'ул. Гагарина, 45', 1980, 'X789YZ77', '2018-03-10');

-- Автомобили
INSERT INTO CARS (LicensePlate, Make, Model, Year, InitialMileage, CurrentMileage, LoadCapacity, FuelType, ImagePath) VALUES
('К456МН77', 'KAMAZ', '5320', 2015, 120000, 130000, 8000, 'Дизель', 'assets/car_images/kamaz.jpg'),
('О789ТР77', 'ГАЗ', '3302', 2018, 80000, 95000, 1500, 'Бензин', 'assets/car_images/gaz.png');

-- Заказы
INSERT INTO ORDERS (OrderDate, DriverID, CarID, StartLocation, EndLocation, Distance, CargoWeight, Price) VALUES
('2024-04-01', 1, 1, 'Москва', 'Санкт-Петербург', 720, 7500, 25000),
('2024-04-05', 2, 2, 'Москва', 'Воронеж', 450, 1200, 12000);

-- Начисления
INSERT INTO EARNINGS (DriverID, OrderID, PeriodStart, PeriodEnd, TotalPrice) VALUES
(1, 1, '2024-04-01', '2024-04-07', 25000),
(2, 2, '2024-04-01', '2024-04-07', 12000);

-- Конфигурация
INSERT INTO APP_CONFIG (ConfigKey, ConfigValue, Description) VALUES
('default_driver_commission', '20', 'Процент вознаграждения водителя'),
('max_cargo_check', 'true', 'Проверять ли превышение грузоподъемности'),
('maintenance_interval_km', '10000', 'Интервал техосмотра в км');
