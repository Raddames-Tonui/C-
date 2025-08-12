Web_service/
│
├── CMakeLists.txt          # Build configuration
├── config.json             # Drogon config (port, SSL, DB creds)
├── sql/                    # Raw SQL scripts
│   ├── schema.sql          # CREATE TABLE ...
│   ├── seed.sql            # Initial data
│   └── queries/            # Organized SQL queries
│       ├── user.sql
│       └── product.sql
│
├── src/
│   ├── main.cpp            # Entry point, server start
│   │
│   ├── controllers/        # HTTP request handlers
│   │   ├── UserController.cpp
│   │   └── ProductController.cpp
│   │
│   ├── db/                 # Database connection & query helpers
│   │   ├── DBConnection.cpp
│   │   └── DBConnection.h
│   │
│   ├── middleware/         # Request filters, logging, auth
│   │   ├── AuthMiddleware.cpp
│   │   └── AuthMiddleware.h
│   │
│   ├── utils/              # Helper functions (JSON, validation, etc.)
│   │   ├── JsonUtils.cpp
│   │   └── JsonUtils.h
│   │
│   └── config/             # Config readers, constants
│       ├── AppConfig.cpp
│       └── AppConfig.h
│
└── tests/                  # Unit & integration tests
├── CMakeLists.txt
├── test_users.cpp
└── test_products.cpp


"SELECT p.pupil_firstname, p.pupil_lastname, c.class_name "
"FROM pupils p "
"INNER JOIN classes c ON p.class_id = c.class_id "
"ORDER BY pupil_firstname DESC;";