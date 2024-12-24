
(cl:in-package :asdf)

(defsystem "serial_port-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Optidata" :depends-on ("_package_Optidata"))
    (:file "_package_Optidata" :depends-on ("_package"))
  ))