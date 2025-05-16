
(cl:in-package :asdf)

(defsystem "ZL_B00-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "pdo_tx_msgs" :depends-on ("_package_pdo_tx_msgs"))
    (:file "_package_pdo_tx_msgs" :depends-on ("_package"))
  ))