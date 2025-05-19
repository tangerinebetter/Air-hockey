# Air hockey
game Air Hockey được làm từ SDL2
![image](https://github.com/user-attachments/assets/1fe7d5ef-2a02-4fa2-8a96-4b6912bb3b39)

Game dựa trên trò chơi Air Hockey thường thấy trong các khu trò chơi ở trung tâm thương mại.

Hướng dẫn chơi:
- Điều khiển bằng 4 phím mũi tên để điều khiển pusher của người chơi.
- Có thể bấm esc để sang setting hoặc dùng chuột bấm nút dừng.
- Setting có thể điều chỉnh âm lượng nhạc nền hoặc âm thanh và độ khó trong và bên ngoài màn chơi.
- Bên nào chạm 5 trước hoặc khi hết thời gian ghi được nhiều điểm hơn thì chiến thắng.
- Độ khó là điều chỉnh về tốc độ của bot, độ khó mặc định là khó.
- Mỗi 5s sẽ xuất hiện power up tăng tốc disk và tạm thời bỏ ma sát ở giữa sân, khi được kích hoạt thì sau 5s sẽ trở lại bình thường.

Các nguồn assets và nguồn tham khảo:
- hit sound: https://pixabay.com/sound-effects/search/retro/ 
- font: Pixeloid by GGBotNet https://www.fontspace.com/category/8-bit
- menu, setting background: @Cronosart99
- các hình còn lại (đĩa, sân đấu, nút bấm, icon....) được vẽ bằng trang web: https://www.pixilart.com/draw?ref=home-page
- header graphics dùng code mẫu của cô
- có tham khảo về phần tính toán va chạm giữa 2 vật thể và hành vi của bot từ trang github: https://github.com/vgladush/air_hockey

Các tính năng trong game:
- menu và setting khi di chuột lên các nút có hiệu ứng
- có thể thay đổi độ to âm lượng của nhạc nền và âm thanh, hoặc tắt bật âm lượng
- thay đổi độ khó trong setting ngay khi chơi
- có thời gian đếm ngược và điểm số hiển thị lên màn hình
- có power up để làm trò chơi thêm thú vị, có hiệu ứng thị giác để nhận biết power up đang được kích hoạt
