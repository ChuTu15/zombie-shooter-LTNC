## Báo cáo bài tập lớn môn lập trình nâng cao - INT2215_1
- Họ và tên: Chu Quang Tú
- MSSV: 21020393
- Tựa game: Zombie shooter
- Thư viện sử dụng: SFML

## 1. Cách lấy và chạy chương trình:
- Bước 1: Download từ github file zip chứa toàn bộ code và thư viện, hình ảnh, âm thanh từ github hoặc dùng lệnh `git clone https://github.com/ChuTu15/zombie-shooter-LTNC.git`
- Bước 2: Giải nén, mở project và chạy chương trình

## 2. Mô tả chung về trò chơi, các ý tưởng chính:
- Trò chơi là một tựa game hành động tiêu diệt xác sống (zombie), điều khiển nhân vật bằng các phím điều hướng - [UP - W], [DOWN - S], [LEFT - A], [RIGHT - D] và dùng chuột để bắn, tiêu diệt những con zombie.
- Ý tưởng chính: 
  + Có 3 loại zombie (bloater, chaser, crawler) với những đặc tính khác nhau đi ra từ các hướng với mục tiêu tấn công người chơi.
  + Mục tiêu của người chơi là di chuyển để né tránh và bắn để tiêu diệt các con zombie để ghi điểm và vượt qua các màn chơi.
  + Mỗi màn chơi sẽ có độ rộng của map thay đổi cũng như số lượng zombie tăng dần theo tường màn. Số màn chơi là vô hạn. Trong mỗi màn chơi cũng sẽ có những vật phẩm hỗ trợ (máu và đạn) xuất hiện bất kỳ trên map để hỗ trợ người chơi. Sau mỗi màn chơi người chơi sẽ được lựa chọn một nâng cấp để tăng sức mạnh của nhân vật.

## 3. Mô tả các chức nâng chính
**Mô tả**:

[Video minh hoạ](https://youtu.be/pqW69Oe9610)

- Tại màn hình khởi chạy lên nhấn `Enter` để bắt đầu game.
- Dùng các phím số `1`, `2`, `3`, `4`, `5`, `6` để lựa chọn nâng cấp.
- Nhân vật có thể di chuyển qua theo các hướng, click chuột trái để bắn đạn về hướng ống ngắm.
- Trong màn hình chính game gồm có score (điểm), high score (điểm cao nhất), ammo (số đạn), health bar (thanh máu), wave (màn chơi hiện tại), zombie (số zombie còn sống).
- Mỗi lần click chuột sẽ bắn 1 viên đạn, khi hết số đạn trong băng người chơi phải reload lại số đạn nếu còn đạn trên người (nhấn `R`). Một băng đạn ban đầu có tối đa 6 viên và có thể thay đổi tuỳ vào nâng cấp nhân vật.
- Sẽ có những vật phẩm rơi ra trong lúc chơi (gồm máu và đạn), di chuyển nhân vật đến để nhặt những vật phẩm đó (bình máu để hồi máu, đạn để tăng lượng đạn đang có trên người).
- Nhấn `P` để tạm dừng và nhấn tiếp `P` để tiếp tục chơi.
- Số lượng màn chơi là vô hạn, qua càng nhiều màn thì map sẽ rộng dần và số lượng zombie sẽ tăng lên tương ứng với số màn.
- Qua mỗi màn người chơi được lựa chọn nâng cấp để mạnh hơn gồm các lựa chọn:
  + Tăng tốc độ bắn
  + Tăng lượng đạn trong băng
  + Tăng lượng máu cơ bản
  + Tăng tốc độ
  + Tăng số lượng và lượng máu hồi của vật phẩm máu
  + Tăng số lượng và lượng đạn của vật phẩm đạn
- Có âm thanh trong lúc chơi như tiếng đạn bắn, nạp đạn, tiếng zombie tấn công,...
- Trò chơi kết thúc khi lượng máu của nhân vật rút về 0, người chơi lựa chọn nhấn `Enter` để chơi lại hoặc `ESC` để out game.

## 4. Các kỹ thuật lập trình được sử dụng trong chương trình
### Các kỹ thuật lập trình
- Sử dụng mảng, các hàm rand(), atan(),...
- Sử dụng các biến const, con trỏ, tham chiếu.
- Sử dụng đọc, viết file.
- Sử dụng class, extern,...
- Phân chia thành các file cpp, header.
### Với thư viện SFML
- Load ảnh định dạng PNG, âm thanh .wav, font chữ.
- Xử lí sự kiện chuột, bàn phím.
- Xử dụng các hàm để xử lí va chạm nhân vật.

## 5. Kết luận, hướng phát triển tựa game trong tương lai.
### Kết luận:
Game về cơ bản đã tương dối hoàn thiện các chức năng cơ bản, đã sử dụng các hàm, thư viện của SFML và phân chia các file thành các file header và cpp. Tuy nhiên phần menu các lựa chọn nâng cấp vẫn còn sơ sài, cơ bản cần phải cải thiện thêm.
### Hướng phát triển trong tương lai:
- Bổ sung thêm hệ thống menu trông đẹp hơn, dùng chuột để lựa chọn.
- Thêm chế độ nhiều người chơi để anh em vào càn quét zombie.
- Thêm các loại súng mới tăng sức mạnh cho nhân vật.
- Số lượng, chủng loại zombie tăng lên.
- Các vật phẩm rơi ra khi tiêu diệt được zombie.
- Thêm skin cho nhân vật đẹp hơn.
- ...
### Những điều tâm đắc:
Trong quá trình làm tựa game này, em đã củng cố được việc sử dụng các thư viện, các hàm và biến trong C++, biết phân chia và quản lý các file header, cpp trong một project. Em cũng đã biết thêm việc kết hợp các thư viện, hàm của một ngôn ngữ thành một chương trình hoàn thiện, qua đó nhận thấy rằng ngôn ngữ lập trình cũng như là một thứ tiếng vậy, không phải chỉ biết rõ các từ là có thể giao tiếp được mà chúng ta cần phải biết kết hợp các từ riêng lẻ đó thành một câu hoàn chỉnh thì mới có thể giao tiếp với những người khác được. Ngoài ra em cũng đã xem rất nhiều video hướng dẫn, đọc các tài liệu, qua đó củng cố được vốn từ tiếng Anh của mình 😛😛. Chính những bài tập lớn như này đã giúp em cải thiện và rèn luyện thêm rất nhiều những kỹ năng lập trình và em cũng hi vọng trong tương lai sẽ được các thầy cô học tập thêm những kỹ năng mới trên con đường trở thành lập trình viên chuyên nghiệp.
