# 無限階層
プランナー2名/プログラマー2名/デザイナー5名/声優2名<br>
計11名で制作したアクションADVゲームです。

## 概要説明
舞台は未来のエビス。新人考古学者リィーネと、その師匠考古学者ロジー博士は、謎多き遺跡「ムゲンカイソウ」の調査へと挑む。<br>
しかし、遺跡に足を踏み入れた瞬間、入口がロックされ、リィーネは遺跡に閉じ込められてしまった。<br>
脱出するには、遺跡に隠された４桁の番号を見つけなければならない。<br>
遺跡を探索するリィーネと外部からサポートするロジー博士。<br>
二人の協力がカギとなる、新感覚協力型アドベンチャーゲーム！<br>
未知の構造、理不尽なギミック、そして待ち受ける真実･･･。<br>
すべてを解き明かし、入口の扉を開けられるか？

## 開発期間
2024/11/28～2025/03/24

## 開発環境
OS：Windows10<br>
言語：C/C++<br>
Microsoft VitualStudio2022<br>
[Dxライブラリ](https://dxlib.xsrv.jp/)<br>
[Effekseer](https://effekseer.github.io/jp/)<br>
[nlomann-json](https://github.com/nlohmann/json)

## 担当箇所
プロジェクト内のソースコードで担当したものを下記に明記します。<br>
ソースコードは、AppFrameフォルダ内とMugenKaisou/Gameフォルダ内の各sourceフォルダにあります。
<details>
<summary>担当箇所詳細</summary>
<pre>

AppFrame（自作ゲームフレームワーク用のライブラリProject）
- コントローラー制御
gamepad
- 計算系処理
MyMath

MugenKaisou（ゲーム本体のProject）
- 3Dゲームモードメイン処理
ModeGame
- キャラクター制御
Chara
- カメラ制御
Camera

- Roomフォルダ（ステージ（部屋）関連）
各ステージ制御
RoomBase
RoomCalcHighLevel
RoomCalcLabyrinth
RoomData
RoomEntrance
RoomMuseum
RoomPizza
RoomSlidePuzzle
ステージデータの読み込み、管理
RoomData
ステージの切り替え
RoomServer
Room.h

- ステージギミック
BeltConveyor
Door
Pizza
ShiftBlock

- 画面効果（フェードインアウト）
Fade
ModeFade
</pre>
</details>

## 起動方法
### プロジェクト
1．上記のプロジェクトをダウンロードし、解凍<br>
2．[Releasesページ](https://github.com/HiroShi09Skr/MugenKaiso/releases)より「res.zip」をダウンロードし、解凍<br>
3．「res」ファイルをプロジェクトの「MugenKaiso/Game」フォルダ内（「source」フォルダと同じ位置）にコピー＆ペースト<br>
4．「MugenKaiso/Game.sln」を起動
### 実行ファイル
[Releasesページ](https://github.com/HiroShi09Skr/MugenKaiso/releases)より「MugenKaisoEXE.zip」をダウンロードし、解凍後「Game.exe」を実行

## 紹介動画
https://github.com/user-attachments/assets/6d437b72-ac00-47e4-9adc-172b9dd1c424

