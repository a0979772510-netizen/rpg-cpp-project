RPG Battle Strategy Simulator (RPG 戰鬥策略模擬器)
這是一個基於 C++ 物件導向技術開發的回合制戰鬥策略模擬器。玩家將扮演勇者與隨機生成的怪物進行戰鬥，體驗包含技能冷卻、閃避、蓄力機制以及進度持久化的完整 RPG 戰鬥體驗。

核心特色 (Core Features)
物件導向架構：利用繼承 (Inheritance) 與多型 (Polymorphism) 設計 Entity 基底類別，實作 Warrior 與 Monster 類別。

隨機戰鬥機制：透過 srand 生成隨機屬性的怪物，並具備隨機蓄力狀態，增加遊戲挑戰性。

豐富戰鬥邏輯：

技能系統：具備冷卻 (Cooldown) 限制。

生存策略：包含閃避機率計算。

動態狀態：怪物蓄力機制（下回合傷害倍增）。

資料持久化：支援遊戲進度儲存 (Save)、載入 (Load) 與重置 (Reset)，透過 fstream 記錄 HP、攻擊力、冷卻狀態與回合數。

UI 操作介面：完整的終端機選單，即時回饋戰況與系統狀態。

系統架構 (System Architecture)
程式碼片段
graph TD
    Main[Main Loop 遊戲主迴圈]:::whitebox
    
    subgraph OOP_Structure [物件導向結構]
        Entity[Entity 基底類別]:::whitebox
        Warrior[Warrior 戰士類別]:::whitebox
        Monster[Monster 怪物類別]:::whitebox
    end
    
    FileIO[檔案 I/O 系統]:::whitebox
    SaveTxt[save.txt 儲存檔案]:::whitebox
    
    Main --> OOP_Structure
    Warrior -->|繼承| Entity
    Monster -->|繼承| Entity
    
    Main --> FileIO
    FileIO --> SaveTxt
開發技術 (Tech Stack)
語言: C++

開發工具: VS Code / C++ Standard (C++11 或以上)

核心技術:

類別繼承與多型

STL Container (std::vector)

檔案處理 (fstream)

隨機數生成 (ctime, cstdlib)

如何編譯與執行
確保目錄下有 Entity.h 與 main.cpp。

使用終端機執行編譯指令：
g++ main.cpp -o rpg_game

執行程式：
./rpg_game

關於作者
本專案為 [物件導向程式設計] 期末專題，由 [蔡棠勛] 開發與維護。

