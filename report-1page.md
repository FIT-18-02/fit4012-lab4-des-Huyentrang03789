# Report 1 page - Lab 4 DES / TripleDES

## Mục tiêu

Bài lab nhằm giúp hiểu rõ cách hoạt động của thuật toán DES và mở rộng sang TripleDES. 
Sinh viên thực hiện mã hóa, giải mã, xử lý nhiều block dữ liệu và áp dụng zero padding.

## Cách làm / Method

- Sử dụng file des.cpp có sẵn làm nền tảng.
- Bổ sung nhập dữ liệu từ bàn phím (stdin) theo mode.
- Cài đặt chia plaintext thành các block 64 bit.
- Thực hiện zero padding cho block cuối.
- Hoàn thiện hàm giải mã DES bằng cách đảo thứ tự round keys.
- Xây dựng TripleDES theo mô hình EDE (Encrypt - Decrypt - Encrypt).
- Viết các test để kiểm tra các trường hợp hợp lệ và không hợp lệ (wrong key, tamper).

## Kết quả / Result

- Chương trình mã hóa và giải mã DES hoạt động đúng.
- Kiểm tra round-trip: decrypt(encrypt(plaintext)) = plaintext.
- Hỗ trợ plaintext dài hơn 64 bit và xử lý đúng multi-block.
- Zero padding được áp dụng đúng cho block cuối.
- TripleDES encrypt/decrypt cho kết quả chính xác.
- Các test negative (wrong key, tamper) cho kết quả khác plaintext như mong đợi.

## Kết luận / Conclusion

Qua bài lab, em hiểu rõ cấu trúc Feistel, cơ chế sinh khóa và quy trình mã hóa của DES. 
Tuy nhiên, DES có độ dài khóa nhỏ nên không còn an toàn trong thực tế.

Hướng mở rộng:
- Cải tiến padding (PKCS#7).
- Tối ưu hiệu năng xử lý nhiều block.
- Áp dụng các thuật toán hiện đại như AES.
