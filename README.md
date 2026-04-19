# AGENT-MANAGEMENT-SYSTEM-CPP
# Agent Management System (C++)

Bu proje, C++ programlama dilinde Nesne Yönelimli Programlama (OOP) ve bellek yönetimi prensiplerini uygulamalı olarak göstermek amacıyla geliştirilmiştir.

## 🚀 Özellikler
- **Polymorphism (Çok Biçimlilik):** Farklı ajan sınıflarının (`Yoru`, `Omen`, `Clove`) ortak bir taban sınıftan (`Agents`) yönetilmesi.
- **Dinamik Bellek Yönetimi:** `new` ve `delete` operatörleri ile manuel bellek kontrolü.
- **Güvenli Temizlik:** Bellek sızıntılarını önlemek için `virtual destructor` ve `clear()` kullanımı.
- **Derin Kopyalama:** Pointer içeren sınıflarda veri güvenliği için Custom Copy Constructor ve Assignment Operator (`operator=`) uygulamaları.
- **Dosya Sistemi:** Ajan verilerinin `Save.txt` dosyasında kalıcı olarak saklanması.

## 📅 Gelişim Planı
- [x] **Faz 1:** Manuel Bellek Yönetimi ve Temel OOP Yapısı (Tamamlandı)
- [ ] **Faz 2:** Modern C++: Smart Pointers (unique_ptr, shared_ptr)
- [ ] **Faz 3:** Veri Yapıları ve Algoritma Optimizasyonları

## 🛠️ Kurulum ve Çalıştırma
Projeyi bilgisayarınıza klonladıktan sonra herhangi bir C++ derleyicisi (Visual Studio, GCC vb.) ile derleyip çalıştırabilirsiniz.
